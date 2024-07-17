_Also reduces GC overhead_
_Basically **Flyweight** Design pattern at play_
```go
type Small struct{
   a int
}

var pool = sync.Pool{
    New : func() interface{}{
        return new(Small);
    }
}

func BenchMarkWithoutPool(b *testing.B){
   var s *Small
   for _= range(b.N){
	   s = &Small{ a:1 }
   }
}

func BenchmarkWithPool(b *testing.B){
   var s *Small
   for _= range(b.N){
      s = pool.Get().(*Small)
      s.a = 1
      pool.Put(s)
   }
}
```

`go test -bench=.`
