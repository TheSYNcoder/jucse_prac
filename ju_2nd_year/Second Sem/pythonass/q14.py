import cProfile

def gen_triplets(limit=None):

    limit = limit if limit is not None else 20
    c = 0 
    m =2 
    while c < limit:
        for n  in range( 1 , m ):
            a = m*m - n*n
            b = 2 * m * n 
            c = m*m + n*n
            if c > limit:
                break
            print( a , b , c )
        m+=1

cProfile.run('gen_triplets()')

'''
3 4 5
8 6 10
5 12 13
15 8 17
12 16 20
         9 function calls in 0.000 seconds

   Ordered by: standard name

   ncalls  tottime  percall  cumtime  percall filename:lineno(function)
        1    0.000    0.000    0.000    0.000 <string>:1(<module>)
        1    0.000    0.000    0.000    0.000 q14.py:3(gen_triplets)
        1    0.000    0.000    0.000    0.000 {built-in method builtins.exec}
        5    0.000    0.000    0.000    0.000 {built-in method builtins.print}
        1    0.000    0.000    0.000    0.000 {method 'disable' of '_lsprof.Profiler' objects}
'''
