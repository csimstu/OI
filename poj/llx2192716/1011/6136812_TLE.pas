program p1011;

var
  totalLength, groupNum, groupLength: longint;
  sticksNum, i: longint;
  Length, group: array[1..10000] of longint;
  used: array[1..10000] of boolean;
  b,OK:boolean;

procedure doit;

  function search(k, currentLength,next : longint): boolean;
    var
      i: integer;
    begin
		if OK then exit(true);
      if (k = groupNum + 1)or(next=sticksNum+1) then
		begin
        OK:=true;
		Exit(true);
		end;
		
      for i := next+1 to sticksNum do
        if (not used[i]) then
        begin
          if (Length[i] = Length[i - 1]) and (not used[i - 1]) then
            Continue;
          if (currentLength + Length[i] > groupLength) then
            Continue;
          if (currentLength + Length[i] = groupLength) then
			begin
            used[i] := true;
			next:=1;
			while used[next] do inc(next);
			used[next]:=true;
			b:=search(k + 1,length[next],next+1);
			used[next]:=false;
			exit(b);
			end;
          if (currentLength + Length[i] < groupLength) then
          begin
            used[i] := true;
            if search(k, currentLength + Length[i], next+1) then
              Exit(true);
            used[i] := false;
          end;
        end;
      Exit(false);
    end;
  begin
    for groupNum := totalLength downto 1 do
      if totalLength mod groupNum = 0 then
        begin
          FillChar(used, SizeOf(used), false);
		  OK:=false;
          groupLength := totalLength div groupNum;
          if search(1, 0, 1) then
            begin
              Writeln(groupLength);
              Exit;
            end;
        end;
  end;

procedure qsort;

  procedure Sort(l, r : longint);
    var
      i, j, x, y: longint;
    begin
      i := l;
      j := r;
      x := Length[sticksNum - (l + r) div 2 + 1];
      repeat
        while Length[sticksNum - i + 1] < x do
          Inc(i);
        while x < Length[sticksNum - j + 1] do
          Dec(j);
        if not (i > j) then
        begin
          y := Length[sticksNum - i + 1];
          Length[sticksNum - i + 1] := Length[sticksNum - j + 1];
          Length[sticksNum - j + 1] := y;
          Inc(i);
          j := j - 1;
        end;
      until i > j;
      if l < j then
        Sort(l, j);
      if i < r then
        Sort(i, r);
    end;
  begin
    Sort(1, sticksNum);
  end;


begin
    while not Eof do
      begin
        Readln(sticksNum);
        if sticksNum = 0 then
          Break
        else
          begin
            totalLength := 0;
            FillChar(Length, SizeOf(Length), 0);
            FillChar(group, SizeOf(group), 0);
            FillChar(used, SizeOf(used), false);
            for i := 1 to sticksNum do
              begin
                Read(Length[i]);
                totalLength := totalLength + Length[i];
              end;
            qsort;
            doit;
          end;
      end;
  end.
