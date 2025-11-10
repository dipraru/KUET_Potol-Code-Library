#!/usr/bin/python3
import os
import subprocess
import hashlib
import shutil
import glob

# Original and stripped directories
orig_dir = "code"
stripped_dir = "code_stripped"

# Prefer original code (preserves indentation); fall back to stripped if needed
code_dir = orig_dir if os.path.isdir(orig_dir) and any(
    os.scandir(orig_dir)
) else stripped_dir

def file_hash(filepath):
    """
    Compute a short SHA-1 hash of the file's contents.
    """
    with open(filepath, 'rb') as f:
        content = f.read()
    return hashlib.sha1(content).hexdigest()[:8]


def get_sections():
    """
    Walk the stripped code directory and collect sections and file metadata.
    Returns:
        List of tuples: (section_name, [(relative_path, subsection_name, number_of_lines, hash_value), ...])
    """
    sections = []
    for root, dirs, files in os.walk(code_dir):
        subsections = []
        section_name = os.path.basename(root)
        if section_name == stripped_dir or section_name == ".":
            continue  # Skip the root of stripped and top-level
        # Sort files for consistent ordering
        for file_name in sorted(files):
            if file_name.startswith('.'):
                continue
            subsection_name = os.path.splitext(file_name)[0]
            relative_path = os.path.join(root, file_name)
            # Count lines and hash content
            try:
                with open(relative_path, 'r', encoding='utf-8', errors='ignore') as f:
                    lines = f.readlines()
                number_of_lines = len(lines)
            except Exception:
                number_of_lines = 0
            hash_value = file_hash(relative_path)
            subsections.append((relative_path, subsection_name, number_of_lines, hash_value))
        if subsections:
            sections.append((section_name, subsections))
    # Sort sections alphabetically
    sections.sort(key=lambda x: x[0].lower())
    return sections


def get_style(filename):
    ext = filename.lower().split('.')[-1]
    if ext in ['c', 'cc', 'cpp', 'h', 'hpp']:
        return 'c++'
    elif ext == 'java':
        return 'java'
    elif ext == 'py':
        return 'python'
    elif ext in ['sh', 'bash']:
        return 'bash'
    else:
        return 'text'


def texify(s):
    """
    Escape special characters for LaTeX.
    """
    return (s.replace('\\', '\\textbackslash{}')
             .replace('_', '\\_')
             .replace('#', '\\#')
             .replace('&', '\\&')
             .replace('%', '\\%')
             .replace('$', '\\$')
             .replace('{', '\\{')
             .replace('}', '\\}')
             .replace('~', '\\textasciitilde{}')
             .replace('^', '\\textasciicircum{}'))


def get_tex(sections):
    """
    Generate LaTeX sections for each code file.
    """
    tex = ''
    for section_name, subsections in sections:
        tex += f'\\section{{{texify(section_name)}}}\n'
        for rel_path, sub_name, n_lines, hval in subsections:
            # Convert Windows backslashes for LaTeX
            input_path = rel_path.replace('\\', '/')
            tex += (f'\\subsection{{\\small {texify(sub_name)}  '
                    f'\\scriptsize [{n_lines} lines] - {hval}}}\n')
            tex += f'\\inputminted{{{get_style(rel_path)}}}{{"{input_path}"}}\n'
        tex += '\n'
    return tex


if __name__ == '__main__':

    print("🔄 Scanning stripped code directory...")
    sections = get_sections()

    print("📝 Generating contents.tex...")
    tex = get_tex(sections)
    with open('contents.tex', 'w', encoding='utf-8') as f:
        f.write(tex)
    print("✅ contents.tex created successfully.")

    print("📄 Compiling notebook.tex to notebook.pdf...")
    try:
        subprocess.run([
            "latexmk", "-pdf", "-shell-escape", "notebook.tex"
        ], check=True)
        print("✅ notebook.pdf compiled successfully.")
        print("🧹 Cleaning up temporary files...")
        # Run latexmk's built-in cleaner first to remove most aux files.
        subprocess.run([
            "latexmk", "-c", "-shell-escape", "notebook.tex"
        ], check=False)

        # Manually remove additional artifacts that latexmk may leave behind.
        temp_file_patterns = [
            "notebook.aux",
            "notebook.fdb_latexmk",
            "notebook.fls",
            "notebook.log",
            "notebook.out",
            "notebook.synctex.gz",
            "notebook.toc",
            "contents.tex"
        ]

        for pattern in temp_file_patterns:
            for temp_path in glob.glob(pattern):
                if os.path.isfile(temp_path):
                    try:
                        os.remove(temp_path)
                    except OSError:
                        pass

        if os.path.isdir('_minted-notebook'):
            try:
                shutil.rmtree('_minted-notebook')
            except OSError:
                pass
    except subprocess.CalledProcessError:
        print("❌ LaTeX compilation failed. Check for errors in the .tex file.")
