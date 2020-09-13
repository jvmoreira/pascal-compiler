program exemplo75 (input, output);
var m,n : integer;
    i: integer;
    b: bool;
begin
  read(n,m);
  b := n or 2;
  b := n > 2;
  m:=n+(m-7)*4;
  n := -m + 4;
  write(m,n);

  n := 0;
  m := 0;
  while (n < 5) do
  begin

    i := 0;
    while(i < n) do
    begin
      write(i);
      i := i + 1;
    end;

    m := m+n;
    n := n + 1;
  end;

end.
