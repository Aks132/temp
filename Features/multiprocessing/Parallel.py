'''
from multiprocessing import Process, Value, Array
import time

def com(n, a):
    while True:
        n.value += 2
        print("pros 1 " + str(n.value))
        time.sleep(1)


def com2(n, a):
    while True:
        n.value += 1
        print('Process 2  ' + str(n.value))

        time.sleep(1)

if __name__ == '__main__':
    num = Value('d', 0.0)
    arr = Array('i', range(5))

    p = Process(target=com, args=(num, arr))
    p2 = Process(target=com2, args=(num, arr))
    p.start()
    p2.start()
    p.join()
    p2.join()

    while True:
        print(num.value)
        print(arr[:])
        time.sleep(1)
'''
values =[5,6,7,8]

for count, value in enumerate(values):
     print(count, value)