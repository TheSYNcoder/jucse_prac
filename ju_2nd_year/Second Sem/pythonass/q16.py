s1 = "always"
s2 = "ways"

table = [[1e9 for _ in range( len(s2) +1 )] for _ in range(len(s1) +1 )]
par = [[None for _ in range( len(s2) +1 )] for _ in range(len(s1) +1 )]

for i in range( 0, len(s1)+1):
    for j in range( 0 , len(s2) + 1) :
        if i == 0 :
            table[i][j] = j 
            
        elif j == 0 :
            table[i][j] = i  
        elif s1[i-1] == s2[j-1]:
            table[i][j] = table[i-1][j-1]
            par[i][j] = [ i -1,  j-1 ]
        else:
            table[i][j] = min( [table[i-1][j-1] , table[i-1][j] , table[i][j-1]]) +1 
            if table[i][j] == table[i-1][j-1]:
                par[i][j] = [ i -1 , j-1 ]
            if table[i][j] == table[i][j-1]:
                par[i][j] = [i , j-1]
            if table[i][j] == table[i-1][j]:
                par[i][j] = [i - 1, j]

i , j = len(s1), len(s2)

print('Minimum changes required :' , table[len(s1)][len(s2)])


# down - delete 
# left - insert 
# diagonal - substitute

def decode( prev , next) :
    if prev[0] == next[0] and next[1] + 1 == prev[1]:
        # left
        return 'I'
    elif prev[1] == next[1] and next[0] + 1 == prev[0]:
        # down
        return 'D'
    else:
        # substitute
        return 'S'



actions =""

while par[i][j] is not None :
    prev = [i , j ] 
    i , j = par[i][j]
    actions += decode( (i , j ) , prev)


if len(actions) != len(s1):
    if i == 0:
        actions += ''.join('I' for _ in range(len(s2) - len(s1)))
    elif j == 0:
        actions += ''.join('D' for _ in range( len(s1) - len(s2)))

actions = actions[::-1]
print('s1 = ' , s1)
print('s2 = ' , s2)
print('Action list to get from s1 to s2 D(for delete) S(for substitute) and I (for insert):\n' , actions)
    





'''
Minimum changes required : 2
s1 =  always
s2 =  ways
Action list to get from s1 to s2 D(for delete) S(for substitute) and I (for insert):
 DDSSSS
'''
