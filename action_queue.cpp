#include <iostream>
#include "action_queue.h"

void action_queue::enqueue(queuetype act)
{
	int newBack = (m_back + 1) % SIZE;
	if (newBack != m_front) //doesn't fill the queue
	{
		m_array[m_back] = act;
		m_back = newBack;
	}
	else
		std::cerr << "Error: Attempt to add new act to action_queue didn't work since action_queue is full.\n";
}

void action_queue::dequeue()
{
	if (!empty())
		m_front = (m_front + 1) % SIZE;
	else
		std::cerr << "Error: Attemp to dequeue from action_queue when it's already empty.\n";
}

void action_queue::calculation(action pact, int pspd, action mact, int mspd)
{
	if (pspd < mspd)
	{
		enqueue(mact);
		enqueue(pact);
	}
	else
	{
		enqueue(pact);
		enqueue(mact);
	}
}

void action_queue::clean()
{
	while (!empty())
		dequeue();
}
