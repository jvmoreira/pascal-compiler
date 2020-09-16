program exemplo75 (input, output);
var m,n :  integer;
function f ( n : integer; var k:integer ) : integer;
var p, q : integer;
begin
   if n<2 then
      begin
         f:=n; k:=0
      end
   else
      begin
         f:=f(n,p) + f(n,q);
         k:=p+q+1
      end;
   write (n, k)
end;
begin
   n:=f(3,m);
   write(n, m)
end.
