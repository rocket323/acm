const maxn=201;
type  gtp=record x,y,next:longint; end;
//=================================================================
var test,n,m,tot:longint;
    first,q:array[0..2*maxn] of longint;
    g:array[0..maxn*maxn] of gtp;
    v:array[0..2*maxn] of boolean;
    f:array[0..maxn,0..maxn] of boolean;
//=================================================================
procedure add(x,y:longint);
begin
 inc(tot);
 g[tot].x:=x; g[tot].y:=y;
 g[tot].next:=first[x]; first[x]:=tot;
end;
//=================================================================
procedure init;
var i,x,y:longint;
begin
 fillchar(first,sizeof(first),0);
 tot:=0;

 readln(n,m);
 
 for i:=1 to m do
 begin
  readln(x,y);
  
  add(x,y+n);
  add(y+n,x);
 end;
end;
//=================================================================
procedure main;
var i,j,k,tail,head,t,x,y,t1,t2,ans:longint;
begin
 fillchar(v,sizeof(v),false);
 fillchar(f,sizeof(f),false);
 f[0,0]:=true;
 ans:=0;
 
 for k:=1 to 2*n do
 if not v[k] then
 begin
  t1:=0; t2:=0;
  tail:=1; head:=1; q[1]:=k; v[k]:=true;
  
  while head<=tail do
  begin
   x:=q[head];
   t:=first[x];
   
   while t<>0 do
   begin
    y:=g[t].y;
    
    if not v[y] then
    begin
     inc(tail);
     q[tail]:=y;
     v[y]:=true;
    end;
    
    t:=g[t].next;
   end;
   
   inc(head);
   
   if x<=n then inc(t1)
           else inc(t2);
  end;
  
  for i:=n div 2 downto t1 do
  for j:=n div 2 downto t2 do
  if not f[i,j] then f[i,j]:=f[i-t1,j-t2];
  
  for i:=n div 2 downto 1 do
  if (f[i,i])and(i>ans) then ans:=i;
 end;
 
 writeln(ans);
end;
//=================================================================
begin

 readln(test);
 while test>0 do
 begin
  init;
  main;
  dec(test);
 end;

end.