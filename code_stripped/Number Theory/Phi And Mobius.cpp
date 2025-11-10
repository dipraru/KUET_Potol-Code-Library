******************phi-1-**********(1-10^6)********
int phi[N];
void make()
{
for(int i=0;i<N;i++)phi[i]=i;
for(int i=1;i<N;i++)
{
for(int j=i+i;j<N;j+=i)phi[j]-=phi[i];
}
}
******************phi-2-*********10^16************
int phi(int n)
{
int ans=1;
int q=sqrt(n);
for(int i=2;i<=q;i++)
{
if(n%i==0)
{
int tem=1;
while(n%i==0)
{
tem*=i;
n/=i;
}
ans=ans*tem/i*(i-1);
q=sqrt(n);
}
}
if(n>1)ans=ans*(n-1);
return ans;
}
************************movious*************
int movious[N];
void make()
{
for(int i=0;i<N;i++)movious[i]=0;
movious[1]=1;
for(int i=1;i<N;i++)
{
for(int j=i+i;j<N;j+=i)movious[j]-=movious[i];
}
}
