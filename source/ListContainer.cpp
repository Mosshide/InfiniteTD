#include "ListContainer.h"

//top left origin
ListContainer::ListContainer()
{
	presence.x = 0;
	presence.y = 0;
	presence.w = 100;
	presence.h = 300;

	noScroll = false;
	itemSelected = -1;
	itemHighlighted = -1;

	elements = nullptr;

	for (int i = 0; i < 3; i++) click[i] = false;

	realign();
}

ListContainer::~ListContainer()
{
	clear();
}

void ListContainer::update()
{
	itemHighlighted = -1;
	for (int i = 0; i < 3; i++) click[i] = false;

	if (elements != nullptr)
	{
		it = elements;
		int sel = 0;
		while (it != nullptr)
		{
			it->updateClipped(presence);
			for (int i = 0; i < 3; i++) if (it->getClick((MouseClick)i) == clickUp) click[i] = true;
			if (it->hovering) itemHighlighted = sel;
			if (it->selected)
			{
				if (sel != itemSelected)
				{
					itemSelected = sel;

					ListElement *its = elements;
					int sels = 0;
					while (its != nullptr)
					{
						if (sels != itemSelected) its->selected = false;
						else its->selected = true;
						its = its->next;
						sels++;
					}
				}
			}

			if (_scrollBar.changed) adjustPosition(it);
			it = it->next;
			sel++;
		}
	}

	_scrollBar.updateClick();
	if (pointInRect(mouse->p, presence))
	{
		if (!noScroll) _scrollBar.updateWheel();
		mouse->lockClick("list container", leftClick);
		mouse->lockClick("list container", rightClick);
		mouse->lockClick("list container", middleClick);
	}
}

void ListContainer::draw()
{
	_bg.draw();

	_scrollBar.draw();
	
	if (elements != nullptr)
	{
		it = elements;
		while (it != nullptr)
		{
			it->drawClipped(presence);
			it = it->next;
		}
	}
}

void ListContainer::adjustPosition(ListElement *it)
{
	if (it->prev != nullptr)
	{
		it->setPosition(presence.x, it->prev->presence.y + it->prev->presence.h + 5);
		it->setWidth(presence.w - 15);
	}
	else
	{
		it->setPosition(presence.x, presence.y - _scrollBar.scrollAmount);
		it->setWidth(presence.w - 15);
	}
}

void ListContainer::adjustPositions()
{
	if (elements != nullptr)
	{
		it = elements;
		while (it != nullptr)
		{
			if (it->prev != nullptr)
			{
				it->setPosition(presence.x, it->prev->presence.y + it->prev->presence.h + 5);
				it->setWidth(presence.w - 15);
			}
			else
			{
				it->setPosition(presence.x, presence.y - _scrollBar.scrollAmount);
				it->setWidth(presence.w - 15);
			}

			it = it->next;
		}
	}
}

void ListContainer::updateScrollLimit()
{
	float tempScrollingLimit = 0.f;

	if (elements != nullptr)
	{
		it = elements;
		while (it != nullptr)
		{
			tempScrollingLimit += (int)it->presence.h + 5;
			it = it->next;
		}
	}

	tempScrollingLimit -= (int)presence.h - 6;
	if (tempScrollingLimit < 0 || noScroll)
	{
		tempScrollingLimit = 0;
	}

	_scrollBar.fitArea(presence.x + presence.w - 6, presence.y + 3, presence.h - 6, tempScrollingLimit);
	_scrollBar.activeArea = presence;
}

void ListContainer::addElement(ListElement *le)
{
	if (elements == nullptr) elements = le;
	else
	{
		it = elements;
		while (it->next != nullptr)
		{
			it = it->next;
		}
		it->next = le;
		le->prev = it;
	}

	updateScrollLimit();
	adjustPositions();
}

void ListContainer::removeElement(int n)
{
	if (elements != nullptr)
	{
		it = elements;
		int i = 0;
		while (it != nullptr)
		{
			if (i == n)
			{
				if (itemSelected == n)
				{
					itemSelected = -1;
				}
				if (itemSelected > n)
				{
					itemSelected -= 1;
				}

				if (it->prev != nullptr)
				{
					it->prev->next = it->next;
				}
				else elements = it->next;
				if (it->next != nullptr) it->next->prev = it->prev;

				delete it;

				updateScrollLimit();

				break;
			}

			it = it->next;
			i++;
		}
		
		if (i < n) printf("LC removeElement: out of bounds %d", n);
		adjustPositions();
	}
}

void ListContainer::clear()
{
	if (elements != nullptr)
	{
		it = elements;
		while (it->next != nullptr)
		{
			it = it->next;
			delete it->prev;
		}
		delete it;

		elements = nullptr;
	}

	updateScrollLimit();
}

void ListContainer::realign()
{
	updateScrollLimit();
	_bg.setRect(presence);
	adjustPositions();
}