Program Gp ;

Const
    Maxn = 10010 ;
    MaxSize = 10100 ;

Var
    first , last , y , val              : array[ 0 .. Maxn * 2 ] of longint ;
    data                                : array[ 0 .. Maxn ] of longint ;
    deep , num                          : array[ 0 .. Maxn ] of longint ;
    use                                 : array[ 0 .. Maxn ] of boolean ;
    sumson , maxson                     : array[ 0 .. Maxn ] of longint ;
    que                                 : array[ 0 .. MaxSize , 1 .. 2 ] of longint ;
    ql , qr                             : longint ;
    n , m                               : longint ;
    ans                                 : longint ;

Procedure Add( p , a , b , c : longint ) ;
begin
    y[ p ] := b ; val[ p ] := c ;
    last[ p ] := first[ a ] ; first[ a ] := p ;
end ;

Procedure Add_Q( l , r : longint ) ;
begin
    if l = r then Exit ;
    Inc( qr ) ;
    que[ qr , 1 ] := l ; que[ qr , 2 ] := r ;
end ;

Procedure Init ;
var
    i , a , b , c                       : longint ;
begin
    fillchar( first , sizeof( first ) , 0 ) ;
    readln( n , m ) ;
    for i := 1 to n - 1 do
    begin
        readln( a , b , c ) ;
        Add( i * 2 - 1 , a , b , c ) ;
        Add( i * 2 , b , a , c ) ;
    end ;
end ;

Procedure Qsort( l , r : longint ) ;
var
    i , j , mid , t                     : longint ;
begin
    i := l ; j := r ; mid := num[ ( l + r ) shr 1 ] ;
    repeat
        while num[ i ] < mid do Inc( i ) ;
        while num[ j ] > mid do Dec( j ) ;
        if i <= j then
        begin
            t := num[ i ] ; num[ i ] := num[ j ] ; num[ j ] := t ;
            Inc( i ) ; Dec( j ) ;
        end ;
    Until i > j ;
    if i < r then Qsort( i , r ) ;
    if l < j then Qsort( l , j ) ;
end ;

Procedure Count( l , r , cici : longint ) ;
var
    i , j                               : longint ;
begin
    Qsort( l , r ) ;
    i := l ; j := r ;
    while i < j do
    begin
        while ( i < j ) and ( num[ i ] + num[ j ] > m ) do Dec( j ) ;
        Inc( ans , ( j - i ) * cici ) ; Inc( i ) ;
    end ;
end ;

Function Maxx( a , b : longint ) : longint ;
begin
    if a > b then Maxx := a else Maxx := b ;
end ;

Procedure Work( l , r : longint ) ;
var
    i                                   : longint ;
    root                                : longint ;
    len , lastp                         : longint ;

    Procedure Dfs_1( rot , father : longint ) ;
    var
        p                           : longint ;
    begin
        sumson[ rot ] := 1 ;
        maxson[ rot ] := 0 ;
        p := first[ rot ] ;
        while p > 0 do
        begin
            if ( use[ y[ p ] ] ) and ( y[ p ] <> father ) then
            begin
                Dfs_1( y[ p ] , rot ) ;
                Inc( sumson[ rot ] , sumson[ y[ p ] ] ) ;
                if sumson[ y[ p ] ] > maxson[ rot ] then
                    maxson[ rot ] := sumson[ y[ p ] ] ;
            end ;
            p := last[ p ] ;
        end ;
    end ;

    Procedure Choose_Root ;
    var
        i                               : longint ;
        cici , min                      : longint ;
    begin
        Dfs_1( data[ l ] , 0 ) ;
        min := n + 1 ;
        for i := l to r do
        begin
            cici := Maxx( maxson[ data[ i ] ] , r - l - sumson[ data[ i ] ] + 1 ) ;
            if cici < min then
            begin
                min := cici ;
                root := data[ i ] ;
            end ;
        end ;
    end ;

    Procedure Dfs_2( rot , father : longint ) ;
    var
        p                           : longint ;
    begin
        Inc( len ) ;
        data[ len ] := rot ; num[ len ] := deep[ rot ] ;
        p := first[ rot ] ;
        while p > 0 do
        begin
            if ( use[ y[ p ] ] ) and ( y[ p ] <> father ) then
            begin
                deep[ y[ p ] ] := deep[ rot ] + val[ p ] ;
                Dfs_2( y[ p ] , rot ) ;
            end ;
            p := last[ p ] ;
            if ( rot = root ) and ( len > lastp ) then
            begin
                Add_Q( lastp + 1 , len ) ;
                Count( lastp + 1 , len , -1 ) ;
                lastp := len ;
            end ;
        end ;
    end ;

    Procedure Updata ;
    var
        i                               : longint ;
    begin
        deep[ root ] := 0 ;
        lastp := l ; len := l - 1 ;
        Dfs_2( root , 0 ) ;
        for i := l + 1 to r do if num[ i ] <= m then Inc( ans ) ;
        Count( l + 1 , r , 1 ) ;
    end ;

begin
    if l = r then Exit ;
    for i := l to r do use[ data[ i ] ] := true ;
    Choose_Root ;
    Updata ;
    for i := l to r do use[ data[ i ] ] := false ;
end ;

Procedure Main ;
var
    i                                   : longint ;
begin
    for i := 1 to n do data[ i ] := i ;
    ans := 0 ;
    ql := 0 ; qr := 1 ;
    que[ 1 , 1 ] := 1 ; que[ 1 , 2 ] := n ;
    repeat
        Inc( ql ) ;
        Work( que[ ql , 1 ] , que[ ql , 2 ] ) ;
    Until ql = qr ;
end ;

Begin
    while not eof do
    begin
        Init ;
        if n + m = 0 then Break ;
        Main ;
        writeln( ans ) ;
    end ;
end .
