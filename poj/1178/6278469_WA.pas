{
ID:yangxia2
PROG:camelot
LANG:PASCAL
}
program comelot;
type
    nit=array[1..16]of integer;
    gtype=array[-100..1040,100..1040]of integer;
var
    //wg,kg:array[-100..1050,-100..1050]of integer;
    //kdis,wdis:array[1..1040,1..1040]of integer;
    wg,kg,kdis,wdis:gtype;
    temp,q,r,c:integer;
    ni:array[-100..10400]of nit;
    sum,worker:array[0..1040]of integer;
    save,last,num,n,i,j,k,p:integer;
    fir,las,king,s,min:integer;
    dui:array[1..100000]of integer;
    fin,fout:text;
procedure init;
var i,j,k:integer;ch,kon:char;
begin
    readln(fin,r,c);n:=r*c;
    readln(fin,ch,kon,i);
    j:=ord(ch)-ord('A')+1;
    king:=(i-1)*c+j;
    num:=0;
    while not(eof(fin)) do
        begin
            while not(eoln(fin)) do
                begin
                    inc(num);
                    //write(1);
                    read(fin,ch);while ch=' ' do read(fin,ch);
                    read(fin,kon,i);
                    //writeln(ch,' ',i);
                    //write(2);
                    j:=ord(ch)-ord('A')+1;
                    worker[num]:=(i-1)*c+j;
                end;
            readln(fin);
        end;
    for i:=1 to n do
        begin
              kg[i,i-c]:=1;
            if i mod c<>0 then if ((i+c-1)div c >=2) then kg[i,i-c+1]:=1;
            if i mod c<>0 then kg[i,i+1]:=1;
            if i mod c<>0 then if ((i-1+c)div c<=r-1) then kg[i,i+c+1]:=1;
              kg[i,i+c]:=1;//
            if i mod c<>1 then if ((i-1+c)div c<=r-1) then kg[i,i+c-1]:=1;
            if i mod c<>1 then kg[i,i-1]:=1;
            if i mod c<>1 then if ((i-1+c)div c>=2) then kg[i,i-c-1]:=1;
        end;
    for i:=1 to n do
        begin
            if i mod c<>0 then if ((i-1+c)div c>=3) then wg[i,i-2*c+1]:=1;
            if (i mod c<c-1)and (i mod c<>0) then if ((i-1+c)div c>=2) then wg[i,i-c+2]:=1;
            if (i mod c<c-1)and (i mod c<>0) then if ((i-1+c)div c<=r-1) then wg[i,i+c+2]:=1;
            if (i mod c<>0) then if ((i-1+c)div c<=r-2) then wg[i,i+2*c+1]:=1;
            if i mod c<>1 then if ((i-1+c)div c<=r-2) then wg[i,i+2*c-1]:=1;
            if (i mod c>=3)or(i mod c=0) then if ((i-1+c)div c<=r-1) then wg[i,i+c-2]:=1;
            if (i mod c>=3)or(i mod c=0) then if ((i-1+c)div c>=2) then wg[i,i-c-2]:=1;
            if i mod c<>1 then if ((i-1+c)div c>=3) then wg[i,i-2*c-1]:=1;
        end;
end;
procedure insert(a:integer;var dis:gtype;y:integer);
var i,j,k,s:integer;
begin
    inc(last);
    dui[last]:=a;
    s:=last;k:=s div 2;
    while k>0 do
        begin
            if dis[y,dui[s]]<dis[y,dui[k]] then
              begin
                temp:=dui[s];dui[s]:=dui[k];dui[k]:=temp;
                s:=s div 2;k:=s div 2;
              end
            else exit;
        end;
end;
procedure del(var a:integer;var dis:gtype;y:integer);
var i,j,k,s:integer;
begin
    a:=dui[1];
    dui[1]:=dui[last];
    dec(last);s:=1;
    while s*2<=last do
        begin
            if s*2=last then j:=last
            else if dis[y,dui[2*s]]<dis[y,dui[2*s+1]] then j:=2*s
                 else j:=2*s+1;
            if dis[y,dui[s]]>dis[y,dui[j]] then
                begin
                    temp:=dui[s];dui[s]:=dui[j];dui[j]:=temp;
                    s:=j;
                end
            else exit;
        end;
end;
procedure minway(var dis,g:gtype;y:integer);
var
    i,j,k:integer;fir,las:integer;
begin
    last:=0;
    for i:=1 to n do dis[y,i]:=10000;
    dis[y,y]:=0;
    insert(y,dis,y);
    for i:=1 to n do
        begin
            del(j,dis,y);
            for k:=1 to 16 do
                begin
                    if g[j,ni[j][k]]=1 then
                        if dis[y,ni[j][k]]>dis[y,j]+1 then
                            begin
                                dis[y,ni[j][k]]:=dis[y,j]+1;//dis[k,y]:=dis[y,j]+1;
                                insert(ni[j][k],dis,y);
                            end;
                end;
        end;
end;

begin

    init;
    for i:=1 to n do
        begin
            ni[i][1]:=i-c;
            ni[i][2]:=i-c+1;
            ni[i][3]:=i+1;
            ni[i][4]:=i+c+1;
            ni[i][5]:=i+c;
            ni[i][6]:=i+c-1;
            ni[i][7]:=i-1;
            ni[i][8]:=i-c-1;
            ni[i][9]:=i-2*c+1;
            ni[i][10]:=i-c+2;
            ni[i][11]:=i+c+2;
            ni[i][12]:=i+2*c+1;
            ni[i][13]:=i+2*c-1;
            ni[i][14]:=i+c-2;
            ni[i][15]:=i-c-2;
            ni[i][16]:=i-2*c-1;
        end;
    minway(kdis,kg,king);
    for i:=1 to n do minway(wdis,wg,i);
    min:=maxint; fillchar(sum,sizeof(sum),0);
    for i:=1 to n do
        for j:=1 to num do
                inc(sum[i],wdis[worker[j],i]);

    for i:=1 to n do{final meet}
        if sum[i]>min then continue else
        for j:=1 to n do{where to pick up the king}
             if sum[i]+kdis[king,j]>min then continue else
             for k:=1 to num do
                begin
                 s:=sum[i]+kdis[king,j]-wdis[worker[k],i]+wdis[worker[k],j]+wdis[j,i];
                 if s<min then
                 min:=s;
                end;
    if num=0 then writeln(fout,0)else writeln(fout,min);

end.







