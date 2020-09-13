program exemplo75 (input, output);
var m,n : integer;
    i: bool;
begin
  read(n,m);
  i := n or 2;
  i := n > 2;
  m:=n+(m-7)*4;
  n := -m + 4;
  write(m,n);
end.
