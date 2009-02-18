#ifndef QPROPERTY_H_
#define QPROPERTY_H_

#include <QObject>
#include <QString>

#include <tulip/AbstractProperty.h>
#include <tulip/PropertyAlgorithm.h>

#include "QNode.h"
#include "QEdge.h"

class QProperty: public QObject {

	Q_OBJECT

public:

	QProperty();
	QProperty(tlp::PropertyInterface*);
	virtual ~QProperty();
	tlp::PropertyInterface* asProperty();

public slots:

	void erase(const QNode*);
	void erase(const QEdge*);
	void copy(const QNode*, const QNode*, QProperty*);
	void copy(const QEdge*, const QEdge*, QProperty*);
	/*virtual PropertyInterface* clonePrototype(Graph *, std::string) =0;
	virtual std::string getTypename() = 0;
	static  std::string getTypename( PropertyInterface * ); */

	// Untyped accessors
	QString getNodeDefaultStringValue();
	QString getEdgeDefaultStringValue();
	QString getNodeStringValue(const QNode *node);
	QString getEdgeStringValue(const QEdge *edge);
	bool setNodeStringValue(const QNode *node, const QString value);
	bool setEdgeStringValue(const QEdge *edge, const QString value);
	bool setAllNodeStringValue(const QString value);
	bool setAllEdgeStringValue(const QString value);
	// the ones below are used by GraphUpdatesRecorder
	/*Iterator<node>* getNonDefaultValuatedNodes()=0;
	 Iterator<edge>* getNonDefaultValuatedEdges()=0;
	 DataMem* getNodeDefaultDataMemValue() = 0;
	 DataMem* getEdgeDefaultDataMemValue() = 0;
	 DataMem* getNodeDataMemValue(const node n) = 0;
	 DataMem* getEdgeDataMemValue(const edge e) = 0;
	 DataMem* getNonDefaultDataMemValue(const node n) = 0;
	 DataMem* getNonDefaultDataMemValue(const edge e) = 0;
	 void setNodeDataMemValue(const node n, const DataMem* v) = 0;
	 void setEdgeDataMemValue(const edge e, const DataMem* v) = 0;
	 void setAllNodeDataMemValue(const DataMem* v) = 0;
	 void setAllEdgeDataMemValue(const DataMem* v) = 0;*/

private:

	tlp::PropertyInterface* _property;

};

#endif /* QPROPERTY_H_ */
