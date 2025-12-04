# KUET Potol - ICPC Team Notebook

A comprehensive algorithm and data structure reference notebook for competitive programming contests, particularly designed for ICPC (International Collegiate Programming Contest).

## Team Members

**Team:** KUET_Potol  
**University:** Khulna University of Engineering & Technology (KUET)

- Mohammad Abu Daud Sharif
- Dipra Datta
- Khadimul Islam Mahi

## Contents

This notebook includes implementations and reference materials for:

- **Combinatorics** - Permutations, combinations, Catalan numbers, Stirling numbers
- **Data Structures** - Advanced data structures for competitive programming
- **Dynamic Programming** - DP optimization techniques and classic problems
- **Flow** - Maximum flow, minimum cost flow algorithms
- **Game Theory** - Nim games, Sprague-Grundy theorem
- **Geometry** - Computational geometry algorithms
- **Graph** - Graph algorithms (DFS, BFS, shortest paths, MST, etc.)
- **Math** - Number theory, combinatorics formulas, and mathematical references
- **Matrix** - Matrix operations and algorithms
- **Miscellaneous** - Utility functions and various algorithms
- **Number Theory** - Prime numbers, GCD, modular arithmetic
- **String** - String processing algorithms (KMP, Z-algorithm, suffix arrays, etc.)

## Prerequisites

### Required Software

- **Python 3.x** - For PDF generation script
- **LaTeX** distribution with the following packages:
  - `pdflatex`
  - `minted` (for syntax highlighting)
  - `geometry`, `hyperref`, `fancyhdr`, `listings`, `xcolor`
  - `tocloft`, `pdflscape`, `multicol`, `titlesec`
  - `amsmath`, `amssymb`, `graphicx`
- **Pygments** - Required by minted package
  ```bash
  pip install Pygments
  ```
- **latexmk** - For automated LaTeX compilation

### Installation

#### On Ubuntu/Debian:
```bash
sudo apt-get update
sudo apt-get install texlive-full python3 python3-pip latexmk
pip3 install Pygments
```

#### On macOS:
```bash
brew install --cask mactex
brew install python3 latexmk
pip3 install Pygments
```

#### On Arch Linux:
```bash
sudo pacman -S texlive-most python python-pip
pip install Pygments
```

## Building the Notebook

### Quick Build

Simply run the Python build script:

```bash
python3 generate_pdf.py
```

This will:
1. Scan the `code/` directory for algorithm implementations
2. Generate `contents.tex` with automatic code inclusion
3. Compile `notebook.tex` to `notebook.pdf`
4. Clean up temporary files

### Manual Build

If you prefer to compile manually:

```bash
pdflatex -shell-escape notebook.tex
pdflatex -shell-escape notebook.tex  # Run twice for TOC
```

**Note:** The `-shell-escape` flag is required for the minted package to work.

## Project Structure

```
.
├── code/                      # Algorithm implementations (original)
│   ├── Combinatorics/
│   ├── Data Structure/
│   ├── Dynamic Programming/
│   ├── Flow/
│   ├── Game Theory/
│   ├── Geometry/
│   ├── Graph/
│   ├── Math/
│   ├── Matrix/
│   ├── Misc/
│   ├── Number Theory/
│   └── String/
├── code_stripped/             # Stripped versions (generated)
├── math/                      # Mathematical formulas and references
├── images/                    # Images and diagrams
├── notebook.tex               # Main LaTeX document
├── contents.tex               # Auto-generated content file
├── generate_pdf.py            # PDF generation script
└── README.md                  # This file
```

## Adding New Algorithms

To add a new algorithm to the notebook:

1. **Add your code file** to the appropriate directory under `code/`:
   ```bash
   # Example: Adding a new graph algorithm
   vim code/Graph/MyNewAlgorithm.cpp
   ```

2. **Follow naming conventions**:
   - Use descriptive filenames
   - Supported extensions: `.cpp`, `.java`, `.py`, `.txt`

3. **Rebuild the PDF**:
   ```bash
   python3 generate_pdf.py
   ```

The script will automatically detect and include the new file in the generated PDF.

## Customization

### Modifying the Template

- **Font sizes**: Edit the `\fontsize` commands in `notebook.tex`
- **Page layout**: Modify geometry settings in the preamble
- **Syntax highlighting**: Adjust minted settings in `notebook.tex`
- **Sections**: Edit `generate_pdf.py` to change section ordering

### Code Formatting

The notebook uses the `minted` package for syntax highlighting with:
- Line numbers
- Automatic line breaking
- Compact formatting optimized for printing

## Tips for Contest Use

1. **Print the PDF** before the contest (if allowed by rules)
2. **Test compilation** before the contest day
3. **Verify all algorithms** are working correctly
4. **Know where to find** specific algorithms in the notebook
5. **Practice using** the notebook during practice sessions

## Common Issues

### Issue: `minted` Error
**Solution:** Ensure Pygments is installed and use `-shell-escape` flag

### Issue: Font Errors
**Solution:** Install the complete TeXLive distribution

### Issue: Missing Packages
**Solution:** Install required LaTeX packages:
```bash
sudo tlmgr install minted fvextra catchfile xstring framed
```

### Issue: Python Script Fails
**Solution:** Check Python version (3.x required) and file permissions

## Output

The final output `notebook.pdf` includes:
- Table of contents with page numbers
- Syntax-highlighted code listings
- Mathematical formulas and theorems
- Optimized for printing in landscape format
- Compact multi-column layout

---

**Last Updated:** December 2025  
**Compiled for:** ICPC and other competitive programming contests
