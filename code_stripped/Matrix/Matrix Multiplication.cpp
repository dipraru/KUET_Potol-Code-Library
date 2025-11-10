const ll M=1e9+7;
const int N=103;
int m;
ll mat[N][N];
ll ans[N][N];
void pow(int po)
{
for(int i=0; i<m; i++)
{
for(int j=0; j<m; j++)ans[i][j]=(i==j);
}
while(po)
{
if(po%2)
{
ll tem[m][m];
for(int i=0; i<m; i++)
{
for(int j=0; j<m; j++)
{
tem[i][j]=0;
for(int k=0; k<m; k++)
{
tem[i][j]+=mat[i][k]*ans[k][j];
tem[i][j]%=M;
}
}
}
for(int i=0; i<m; i++)
{
for(int j=0; j<m; j++)
{
ans[i][j]=tem[i][j];
}
}
}
po=po/2;
ll tem[m][m];
for(int i=0; i<m; i++)
{
for(int j=0; j<m; j++)
{
tem[i][j]=0;
for(int k=0; k<m; k++)
{
tem[i][j]+=mat[i][k]*mat[k][j];
tem[i][j]%=M;
}
}
}
for(int i=0; i<m; i++)
{
for(int j=0; j<m; j++)
{
mat[i][j]=tem[i][j];
}
}
}
return ;
}
