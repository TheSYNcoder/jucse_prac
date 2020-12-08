
import random
with open( 'input.txt' , 'w') as f:
    for i in range(100000):
        a = random.randint(0 , 100000)
        f.write(str(a))
        f.write('\n')
f.close()