program poj1321;
var
b:array[1..8,1..8] of boolean;
l,r:array[1..8] of boolean;
ans,i,j,n,k:longint;
ch:char;

procedure search(i,j,dep:longint);
begin
if dep>k then
	begin
	inc(ans);
	exit;
	end;
if (i<1)or(i>n)or(j<1)or(j>n) then exit;
if (not(r[i] and l[j]))or b[i,j] then
	begin
	if j=n then search(i+1,1,dep)
	else
		search(i,j+1,dep);
	exit;
	end;

r[i]:=false; l[j]:=false;
search(i+1,1,dep+1);
r[i]:=true; l[j]:=true;

if j=n then search(i+1,1,dep)
	else
		search(i,j+1,dep);

end;

begin
assign(input,'t.in'); reset(input);
assign(output,'t.out'); rewrite(output);
while not eof do
begin
readln(n,k);
if n=-1 then break;
fillchar(b,sizeof(b),false);
fillchar(r,sizeof(r),true);
fillchar(l,sizeof(l),true);
for i:=1 to n do
	begin
	for j:=1 to n do
		begin
		read(ch);
		if ch='.' then
			b[i,j]:=true;{if [i,j] is block}
		end;
	readln;
	end;
ans:=0;
search(1,1,1);
writeln(ans);
end;
close(input); close(output);
end.
