import random
import concurrent.futures as cf

import os
import time





def worker(port, args, host, destport):
    args = ' '.join(arg for arg in args)
    command = 'python3 client.py {} {} {} {}'.format(
        host, destport, port, args)
    os.system(command)
    


def test():
    ports = [3000 + i for i in range(1000)]


    destport = '64432'
    host = '127.0.0.1'
    NUM_CPUS = None
    keys = ['key' + str(i) for i in range(1, 1000)]


    vals = ['val' + str(i) for i in range(1, 1000)]


    arglist = []
    for _ in range(100):
        all_keys = random.choices(keys, k=random.randint(3, 50))
        curr_arg = []
        for key in all_keys:
            if random.random() > 0.5:
                curr_arg.append('put')
                curr_arg.append(key)
                curr_arg.append(random.choice(vals))
            else:
                curr_arg.append('get')
                curr_arg.append(key)

        arglist.append(curr_arg)


    futures = []
    start = time.time()
    org = ports
    total =0
    
    with cf.ThreadPoolExecutor(NUM_CPUS) as pool:
        for arg in arglist:
            for port in ports[:10]:
                total+=1
                futures.append(pool.submit(worker, port, arg, host, destport))
            ports = ports[10:]
            if ports[0] > 3200:
                ports = org



        for future in cf.as_completed(futures):
            future.result()
            # print( time.time() - start )
            # if time.time() - start > 30:
            #     ports = org
            #     start = time.time()
    
    end = time.time() - start
    print( 'total time : ', end / 60 )
    print('Total Requests :' , total , ' Avg. Request Time : ' , end / (60 * total) , ' s')


if __name__ == '__main__':
    test()



'''

Stats
Normal Server Multithreaded
total time :  169.3963410854339700
Total Requests : 1000  Avg. Request Time :  0.1693963410854339700  s

Stats
Select UnBlocking Server
total time :  247.88802623748780
Total Requests : 1000  Avg. Request Time :  0.24788802623748780  s



'''
