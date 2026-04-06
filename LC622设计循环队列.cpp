int circlequene[];
int l, r, size, limit;
class MyCircularQueue {
public:
    MyCircularQueue(int k) {
        l = 0, r = 0, size = 0;
        //l，r表示头和尾，size表示元素个数
        limit = k;
        //limit表示最大容量，即队列长度
    }

    //enQueue(value): 向循环队列插入一个元素。
    //如果成功插入则返回真。
    bool enQueue(int value) {
        if (isFull())
        {
            return false;
        }
        else 
        {
            circlequene[r] = value;
            r = (r + 1) % limit;
            size++;
            return true;
        }
    }


    //deQueue(): 从循环队列中删除一个元素。如果成功删除则返回真。
    bool deQueue() {
        if (isEmpty())
        {
            return false;
        }
        else 
        {
            l = (l + 1) % limit;
            size--;
            return true;
        }
    }

    //Front: 从队首获取元素。如果队列为空，返回 -1 。
    int Front() {
        if (isEmpty())
        {
            return -1;
        }
        else 
        {
            return circlequene[l];
        }
    }

    //Rear: 获取队尾元素。如果队列为空，返回 -1 。
    int Rear() {
        if (isEmpty())
        {
            return -1;
        }
        else
        {
            r = (r - 1 + limit) % limit;
            return circlequene[r-1];
        }
    }

    bool isEmpty() {
        return size == 0;

    }

    bool isFull() {
        return size == limit;
    }
};

/**
 * Your MyCircularQueue object will be instantiated and called as such:
 * MyCircularQueue* obj = new MyCircularQueue(k);
 * bool param_1 = obj->enQueue(value);
 * bool param_2 = obj->deQueue();
 * int param_3 = obj->Front();
 * int param_4 = obj->Rear();
 * bool param_5 = obj->isEmpty();
 * bool param_6 = obj->isFull();
 */