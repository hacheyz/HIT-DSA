#ifndef HW2_QUEUE_H
#define HW2_QUEUE_H

template<class T>
class QNode
{
public:
	T data;
	QNode *next;

	QNode() : next(NULL)
	{
	}
};

template<typename T>
class Queue
{
private:
	QNode<T> *front;    // front->next是存放数据的第一个结点
	QNode<T> *rear;        // 始终指向队列的最后一个结点
public:
	Queue();
	bool isEmpty();
	void push(T x);
	T pop();
	T getFront();
};

template<typename T>
Queue<T>::Queue()
{
	front = new QNode<T>;
	front->next = NULL;
	rear = front;
}

template<typename T>
bool Queue<T>::isEmpty()
{
	return front == rear;
}

template<typename T>
void Queue<T>::push(T x)
{
	QNode<T> *temp = new QNode<T>;
	temp->data = x;
	temp->next = NULL;
	rear->next = temp;
	rear = temp;
}

template<typename T>
T Queue<T>::pop()
{
	if (isEmpty())
	{
		std::cout << "队空" << std::endl;
		exit(21);    // 队空，错误码21
	}
	QNode<T> *toPop = front->next;
	T ret = toPop->data;
	front->next = front->next->next;
	if (front->next == NULL)
		rear = front;
	delete toPop;
	return ret;
}

template<typename T>
T Queue<T>::getFront()
{
	if (isEmpty())
	{
		std::cout << "队空" << std::endl;
		exit(21);    // 队空，错误码21
	}
	return front->next->data;
}

#endif //HW2_QUEUE_H
