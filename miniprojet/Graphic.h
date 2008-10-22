/*
 * IGraphicContainer.h
 *
 *  Created on: 16 oct. 2008
 *      Author: rnappee
 */

#ifndef ICURVECONTAINER_H_
#define ICURVECONTAINER_H_

#include <QGraphicsItemGroup>

#include "Observer.h"
#include "IData.h"

template <typename T>
class Graphic : public QGraphicsItemGroup, public Observer
{
	public :
		virtual void setGraphic(IData<T>*) = 0;
		virtual IData<T>* getGraphic() = 0;
		virtual void setScale(float) = 0;
		virtual float getScale() = 0;

		virtual void update(Observable * subject) = 0;
};

#endif /* IGraphicContainer_H_ */