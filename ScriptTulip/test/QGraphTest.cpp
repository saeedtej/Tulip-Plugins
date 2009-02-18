#include <cppunit/TestCase.h>
#include <cppunit/TestCaller.h>
#include <tulip/ForEach.h>
#include "QGraphTest.h"
#include <tulip/BooleanProperty.h>
#include <tulip/DoubleProperty.h>
#include <tulip/IntegerProperty.h>
#include "QGraph.h"


using namespace std;
using namespace tlp;

CPPUNIT_TEST_SUITE_REGISTRATION( QGraphTest );

//==========================================================
void QGraphTest::setUp() {
  graph = new QGraph();
}
//==========================================================
void QGraphTest::tearDown() {
  delete graph;
}
//==========================================================
void QGraphTest::build(unsigned int nbNodes, unsigned int edgeRatio) {
  vector<QNode*> nodes;
  vector<QEdge*> edges;
  unsigned int NB_ADD  = nbNodes;
  unsigned int EDGE_RATIO = edgeRatio;
  for (unsigned int i=0; i<NB_ADD; ++i)
    nodes.push_back(graph->addNode());
  unsigned int NB_EDGES = EDGE_RATIO * NB_ADD;
  for (unsigned int i=0; i< NB_EDGES; ++i)
    graph->addEdge(nodes[rand()%NB_ADD], nodes[rand()%NB_ADD]);
}
//==========================================================
void QGraphTest::testIterators() {
  graph->clear();
  vector<QNode*> nodes;
  vector<QEdge*> edges;
  unsigned int NB_NODES  = 100;
  unsigned int EDGE_RATIO = 100;
  for (unsigned int i=0; i<NB_NODES; ++i)
    nodes.push_back(graph->addNode());
  unsigned int NB_EDGES = EDGE_RATIO * NB_NODES;
  for (unsigned int i=0; i< NB_EDGES; ++i)
    edges.push_back(graph->addEdge(nodes[rand()%NB_NODES], nodes[rand()%NB_NODES]));
  {
  QIterator *itN = graph->getNodes();
  unsigned int i = 0;
  while(itN->hasNext()){
    CPPUNIT_ASSERT_EQUAL( nodes[i]->asNode().id , ((QNode*)(itN->next()))->asNode().id );
    ++i;
  }delete itN;
  CPPUNIT_ASSERT_EQUAL( i , NB_NODES );
  }
  {
	  QIterator *itE = graph->getEdges();
  unsigned int i = 0;
  while(itE->hasNext()){
    CPPUNIT_ASSERT_EQUAL( edges[i]->asEdge().id , ((QEdge*)(itE->next()))->asEdge().id );
    ++i;
  }delete itE;
  CPPUNIT_ASSERT_EQUAL( i , NB_EDGES );
  }
  graph->clear();
  QNode *n1 = graph->addNode();
  QNode *n2 = graph->addNode();
  QNode *n3 = graph->addNode();
  QEdge *e1 = graph->addEdge(n1, n1); //loop
  QEdge *e2 = graph->addEdge(n1, n2);
  QEdge *e3 = graph->addEdge(n2, n1);//parallel edge
  QEdge *e4 = graph->addEdge(n1, n3);

  QIterator *it1 = graph->getOutNodes(n1);
  CPPUNIT_ASSERT_EQUAL(n1->asNode().id, ((QNode*)(it1->next()))->asNode().id);
  CPPUNIT_ASSERT_EQUAL(n2->asNode().id, ((QNode*)(it1->next()))->asNode().id);
  CPPUNIT_ASSERT_EQUAL(n3->asNode().id, ((QNode*)(it1->next()))->asNode().id);
  CPPUNIT_ASSERT_EQUAL(false, it1->hasNext());
  delete it1;
  QIterator *it2 = graph->getInNodes(n1);
  CPPUNIT_ASSERT_EQUAL(n1->asNode().id, ((QNode*)(it2->next()))->asNode().id);
  CPPUNIT_ASSERT_EQUAL(n2->asNode().id, ((QNode*)(it2->next()))->asNode().id);
  CPPUNIT_ASSERT_EQUAL(false, it2->hasNext());
  delete it2;
  QIterator *it3 = graph->getInOutNodes(n1);
  CPPUNIT_ASSERT_EQUAL(n1->asNode().id, ((QNode*)(it3->next()))->asNode().id);
  CPPUNIT_ASSERT_EQUAL(n1->asNode().id, ((QNode*)(it3->next()))->asNode().id);
  CPPUNIT_ASSERT_EQUAL(n2->asNode().id, ((QNode*)(it3->next()))->asNode().id);
  CPPUNIT_ASSERT_EQUAL(n2->asNode().id, ((QNode*)(it3->next()))->asNode().id);
  CPPUNIT_ASSERT_EQUAL(n3->asNode().id, ((QNode*)(it3->next()))->asNode().id);
  CPPUNIT_ASSERT_EQUAL(false, it3->hasNext());
  delete it3;

  QIterator *it4 = graph->getOutEdges(n1);
  CPPUNIT_ASSERT_EQUAL(e1->asEdge().id, ((QEdge*)(it4->next()))->asEdge().id);
  CPPUNIT_ASSERT_EQUAL(e2->asEdge().id, ((QEdge*)(it4->next()))->asEdge().id);
  CPPUNIT_ASSERT_EQUAL(e4->asEdge().id, ((QEdge*)(it4->next()))->asEdge().id);
  CPPUNIT_ASSERT_EQUAL(false, it4->hasNext());
  delete it4;
  QIterator *it5 = graph->getInEdges(n1);
  CPPUNIT_ASSERT_EQUAL(e1->asEdge().id, ((QEdge*)(it5->next()))->asEdge().id);
  CPPUNIT_ASSERT_EQUAL(e3->asEdge().id, ((QEdge*)(it5->next()))->asEdge().id);
  CPPUNIT_ASSERT_EQUAL(false, it5->hasNext());
  delete it5;
  QIterator *it6 = graph->getInOutEdges(n1);
  CPPUNIT_ASSERT_EQUAL(e1->asEdge().id, ((QEdge*)(it6->next()))->asEdge().id);
  CPPUNIT_ASSERT_EQUAL(e1->asEdge().id, ((QEdge*)(it6->next()))->asEdge().id);
  CPPUNIT_ASSERT_EQUAL(e2->asEdge().id, ((QEdge*)(it6->next()))->asEdge().id);
  CPPUNIT_ASSERT_EQUAL(e3->asEdge().id, ((QEdge*)(it6->next()))->asEdge().id);
  CPPUNIT_ASSERT_EQUAL(e4->asEdge().id, ((QEdge*)(it6->next()))->asEdge().id);
  CPPUNIT_ASSERT_EQUAL(false, it6->hasNext());
  delete it6;
}
//==========================================================
void degreeCheck(QGraph *graph) {
  QIterator *itN = graph->getNodes();
  while (itN->hasNext()) {
    QNode *n = (QNode*)itN->next();
    unsigned int outdeg = 0;
    unsigned int indeg = 0;
    unsigned int deg = 0;
    QIterator *it = graph->getOutEdges(n);
    for (;it->hasNext();it->next())
      ++outdeg;
    delete it;
    it = graph->getInEdges(n);
    for (;it->hasNext();it->next())
      ++indeg;
    delete it;
    it = graph->getInOutEdges(n);
    for (;it->hasNext();it->next())
      ++deg;
    delete it;
    CPPUNIT_ASSERT_EQUAL(graph->indeg(n) , indeg);
    CPPUNIT_ASSERT_EQUAL(graph->outdeg(n), outdeg);
    CPPUNIT_ASSERT_EQUAL(graph->deg(n)   , deg);
    CPPUNIT_ASSERT_EQUAL(indeg + outdeg  , deg);
  } delete itN;
}
//==========================================================
void QGraphTest::testDegree() {
  graph->clear();
  build(100, 100);
  degreeCheck(graph);
  QGraph *gr = graph->clone();
  QGraph *gr1 = graph->clone();
  QGraph *gr2 = gr1->clone();

  degreeCheck(graph);
  degreeCheck(gr);
  degreeCheck(gr1);
  degreeCheck(gr2);
  QIterator *it = graph->getEdges();
  while(it->hasNext()) {
    graph->reverse((QEdge*)it->next());
  } delete it;
  degreeCheck(graph);
  degreeCheck(gr);
  degreeCheck(gr1);
  degreeCheck(gr2);
  it = gr2->getEdges();
  while(it->hasNext()) {
    gr2->reverse((QEdge*)it->next());
  } delete it;
  degreeCheck(graph);
  degreeCheck(gr);
  degreeCheck(gr1);
  degreeCheck(gr2);

  graph->clear();
  graph->clear();
  QNode* n1 = graph->addNode();
  QNode* n2 = graph->addNode();
  QNode* n3 = graph->addNode();
  graph->addEdge(n1, n2);
  graph->addEdge(n1, n3);
  graph->delNode(n3);
  CPPUNIT_ASSERT_EQUAL(2u, graph->numberOfNodes());
  CPPUNIT_ASSERT_EQUAL(1u, graph->numberOfEdges());
  CPPUNIT_ASSERT_EQUAL(0u, graph->indeg(n1));
  CPPUNIT_ASSERT_EQUAL(1u, graph->indeg(n2));
  CPPUNIT_ASSERT_EQUAL(1u, graph->outdeg(n1));
  CPPUNIT_ASSERT_EQUAL(0u, graph->outdeg(n2));
  CPPUNIT_ASSERT_EQUAL(1u, graph->deg(n1));
  CPPUNIT_ASSERT_EQUAL(1u, graph->deg(n2));

}
//==========================================================
void QGraphTest::testAddDel() {
  //  cerr << __PRETTY_FUNCTION__ << endl;
  vector<QNode*> nodes;
  vector<QEdge*> edges;
  unsigned int NB_ADD = 100;
  unsigned int EDGE_RATIO = 100;

  unsigned int NB_EDGES = EDGE_RATIO * NB_ADD;
  vector<bool> edgePresent(NB_EDGES);
  vector<bool> nodePresent(NB_ADD);

  for (unsigned int i=0; i<NB_ADD; ++i) {
    nodes.push_back(graph->addNode());
    CPPUNIT_ASSERT(graph->isElement(nodes[i]));
    nodePresent[i] = true;
  }
  CPPUNIT_ASSERT(graph->numberOfNodes() == NB_ADD);


  for (unsigned int i=0; i< NB_EDGES; ++i) {
    edges.push_back(graph->addEdge(nodes[rand()%NB_ADD],nodes[rand()%NB_ADD]));
    CPPUNIT_ASSERT(graph->isElement(edges[i]));
    edgePresent[i] = true;
  }
  CPPUNIT_ASSERT(graph->numberOfEdges() == NB_EDGES);

  for (unsigned int i=0; i < NB_EDGES / 2; ++i) {
    graph->delEdge(edges[i]);
    CPPUNIT_ASSERT(!graph->isElement(edges[i]));
  }
  CPPUNIT_ASSERT(graph->numberOfEdges() == NB_EDGES - NB_EDGES/2);

  for (unsigned int i=0; i<NB_ADD; ++i) {
    QIterator *itE = graph->getInOutEdges(nodes[i]);
    while (itE->hasNext())
      CPPUNIT_ASSERT(graph->isElement((QEdge*)itE->next()));
    delete itE;
    graph->delNode(nodes[i]);
    CPPUNIT_ASSERT(!graph->isElement(nodes[i]));
  }
  CPPUNIT_ASSERT(graph->numberOfNodes() == 0);
  CPPUNIT_ASSERT(graph->numberOfEdges() == 0);
}
//==========================================================
void QGraphTest::testClear() {
  build(100, 100);
  graph->clear();
  CPPUNIT_ASSERT(graph->numberOfNodes() == 0);
  CPPUNIT_ASSERT(graph->numberOfEdges() == 0);
}
//==========================================================
void QGraphTest::testOrderEdgeAndSwap() {
  graph->clear();
  vector<QNode*> nodes;
  vector<QEdge*> edges;
  unsigned int NB_NODES = 1000;
  for (unsigned int i=0; i<NB_NODES; ++i)
    nodes.push_back(graph->addNode());
  unsigned int NB_EDGES = NB_NODES - 1;
  for (unsigned int i=0; i<NB_EDGES; ++i)
    edges.push_back(graph->addEdge(nodes[0],nodes[i+1]));
  {
    QIterator *it = graph->getInOutEdges(nodes[0]);
    unsigned int i = 0;
    while(it->hasNext()) {
      CPPUNIT_ASSERT( ((QEdge*)it->next())->asEdge() == edges[i]->asEdge());
      ++i;
    }delete it;
  }
  //change order
  for (unsigned int j=0;j < NB_EDGES; ++j) {
    unsigned int u = rand()%NB_EDGES;
    unsigned int v = rand()%NB_EDGES;
    QEdge* tmp = edges[u];
    edges[u] = edges[v];
    edges[v] = tmp;
  }
  graph->setEdgeOrder(nodes[0],edges);
  {
    QIterator *it = graph->getInOutEdges(nodes[0]);
    unsigned int i = 0;
    while(it->hasNext()) {
    	CPPUNIT_ASSERT( ((QEdge*)it->next())->asEdge() == edges[i]->asEdge());
      ++i;
    }delete it;
  }
  //Swap two edge
  for (unsigned int j=0;j < NB_EDGES; ++j) {
    unsigned int u = rand()%NB_EDGES;
    unsigned int v = rand()%NB_EDGES;
    graph->swapEdgeOrder(nodes[0],edges[u],edges[v]);
    QEdge* tmp = edges[u];
    edges[u] = edges[v];
    edges[v] = tmp;
  }
  {
    QIterator *it = graph->getInOutEdges(nodes[0]);
    unsigned int i = 0;
    while(it->hasNext()) {
    	CPPUNIT_ASSERT( ((QEdge*)it->next())->asEdge() == edges[i]->asEdge());
      ++i;
    }delete it;
  }
  graph->clear();
}
//==========================================================
void QGraphTest::testDeleteSubgraph() {
  graph->clear();
  QGraph *g1, *g2, *g3, *g4;
  g1 = graph->addSubGraph();
  g2 = graph->addSubGraph();
  g3 = g2->addSubGraph();
  g4 = g2->addSubGraph();

  CPPUNIT_ASSERT(graph->getSuperGraph()->asGraph()==graph->asGraph());
  CPPUNIT_ASSERT(g1->getSuperGraph()->asGraph()==graph->asGraph());
  CPPUNIT_ASSERT(g2->getSuperGraph()->asGraph()==graph->asGraph());
  CPPUNIT_ASSERT(g3->getSuperGraph()->asGraph()==g2->asGraph());
  CPPUNIT_ASSERT(g4->getSuperGraph()->asGraph()==g2->asGraph());

  CPPUNIT_ASSERT(graph->getRoot()->asGraph()==graph->asGraph());
  CPPUNIT_ASSERT(g1->getRoot()->asGraph()==graph->asGraph());
  CPPUNIT_ASSERT(g2->getRoot()->asGraph()==graph->asGraph());
  CPPUNIT_ASSERT(g3->getRoot()->asGraph()==graph->asGraph());
  CPPUNIT_ASSERT(g4->getRoot()->asGraph()==graph->asGraph());

  graph->delSubGraph(g2);
  CPPUNIT_ASSERT(graph->getSuperGraph()->asGraph()==graph->asGraph());
  CPPUNIT_ASSERT(g1->getSuperGraph()->asGraph()==graph->asGraph());
  CPPUNIT_ASSERT(g3->getSuperGraph()->asGraph()==graph->asGraph());
  CPPUNIT_ASSERT(g4->getSuperGraph()->asGraph()==graph->asGraph());

  graph->delSubGraph(g3);
  graph->delSubGraph(g4);
  g2 = g1->addSubGraph();
  g3 = g2->addSubGraph();
  g4 = g3->addSubGraph();
  g1->delAllSubGraphs(g2);
  /*Iterator<Graph *> *itGr = g1->getSubGraphs();
  CPPUNIT_ASSERT(!itGr->hasNext());
  delete itGr;*/
  graph->clear();
}
//==========================================================

void QGraphTest::testSubgraphId() {
  graph->clear();
  BooleanProperty* sel = new BooleanProperty(graph->asGraph());
  QGraph *g1 = graph->addSubGraph(sel);
  int id = g1->getId();
  for (unsigned int i = 1; i<1000; ++i) {
    g1 = graph->addSubGraph(sel);
    CPPUNIT_ASSERT(g1->getId() == (int)(id + i));
  }

  unsigned int i = 0; //if the graph are not ordered that test can fail.

  QIterator *it = graph->getSubGraphs();

  while(it->hasNext()) {
	  CPPUNIT_ASSERT(((QGraph*)it->next())->getId() == (int)(id + i));
	     ++i;
  }delete it;
  delete sel;
}
//==========================================================

void QGraphTest::testSubgraph() {
  graph->clear();
  QGraph *g1, *g2, *g3, *g4;
  g1 = graph->addSubGraph();
  g2 = graph->addSubGraph();
  g3 = g2->addSubGraph();
  g4 = g2->addSubGraph();

  CPPUNIT_ASSERT(graph->getSuperGraph()->getId()==graph->getId());
  CPPUNIT_ASSERT(g1->getSuperGraph()->getId()==graph->getId());
  CPPUNIT_ASSERT(g2->getSuperGraph()->getId()==graph->getId());
  CPPUNIT_ASSERT(g3->getSuperGraph()->getId()==g2->getId());
  CPPUNIT_ASSERT(g4->getSuperGraph()->getId()==g2->getId());

  CPPUNIT_ASSERT(graph->getRoot()->getId()==graph->getId());
  CPPUNIT_ASSERT(g1->getRoot()->getId()==graph->getId());
  CPPUNIT_ASSERT(g2->getRoot()->getId()==graph->getId());
  CPPUNIT_ASSERT(g3->getRoot()->getId()==graph->getId());
  CPPUNIT_ASSERT(g4->getRoot()->getId()==graph->getId());

  QIterator *it = g2->getSubGraphs();
  QGraph *a,*b;
  CPPUNIT_ASSERT(it->hasNext());
  a = (QGraph*)(it->next());
  CPPUNIT_ASSERT(it->hasNext());
  b = (QGraph*)(it->next());
  CPPUNIT_ASSERT((a->getId()==g3->getId() && b->getId()==g4->getId()) || (a->getId()==g4->getId() && b->getId()==g3->getId()));
  CPPUNIT_ASSERT(!it->hasNext());
  delete it;
  g2->clear();
  it= g2->getSubGraphs();
  CPPUNIT_ASSERT(!it->hasNext());
  delete it;

  g3 = g2->addSubGraph();
  g4 = g2->addSubGraph();
  QNode* n1 = g3->addNode();
  QNode* n2 = g3->addNode();
  CPPUNIT_ASSERT(g3->isElement(n1) && g3->isElement(n2));
  CPPUNIT_ASSERT(g2->isElement(n1) && graph->isElement(n1));
  CPPUNIT_ASSERT(g2->isElement(n2) && graph->isElement(n2));
  CPPUNIT_ASSERT(!g4->isElement(n1) && !g1->isElement(n1));
  CPPUNIT_ASSERT(!g4->isElement(n2) && !g1->isElement(n2));

  QEdge *e = g2->addEdge(n1,n2);
  CPPUNIT_ASSERT(!g3->isElement(e) && !g4->isElement(e) && !g1->isElement(e));
  CPPUNIT_ASSERT(g2->isElement(e) && graph->isElement(e) && g2->isElement(n2));
  g2->delNode(n2);
  CPPUNIT_ASSERT(!g2->isElement(n2) && !g2->isElement(e));
  CPPUNIT_ASSERT(graph->isElement(n2) && graph->isElement(e));
  g2->addNode(n2);
  g2->addEdge(e);
  CPPUNIT_ASSERT(g2->isElement(n2) && g2->isElement(e));
  g2->delAllNode(n2);
  CPPUNIT_ASSERT(!g2->isElement(n2) && !g2->isElement(e));
  CPPUNIT_ASSERT(!graph->isElement(n2) && !graph->isElement(e));
  graph->clear();

  g1 = graph->addSubGraph();
  g2 = graph;
  graph = g1;
  testAddDel();
  testClear();
  testOrderEdgeAndSwap();
  testIterators();
  graph = g2;
  graph->clear();
}
//==========================================================
void QGraphTest::testInheritance() {
  graph->clear();
  QGraph *g1, *g2, *g3, *g4;

  g1 = graph->addSubGraph();
  g2 = graph->addSubGraph();
  g3 = g2->addSubGraph();
  g4 = g2->addSubGraph();
  QProperty *m = graph->getDoubleProperty("metric");
  CPPUNIT_ASSERT(graph->existProperty("metric"));
  CPPUNIT_ASSERT(g1->existProperty("metric"));
  CPPUNIT_ASSERT(g2->existProperty("metric"));
  CPPUNIT_ASSERT(g3->existProperty("metric"));
  CPPUNIT_ASSERT(g4->existProperty("metric"));

  graph->delLocalProperty("metric");
  CPPUNIT_ASSERT(!graph->existProperty("metric"));
  CPPUNIT_ASSERT(!g1->existProperty("metric"));
  CPPUNIT_ASSERT(!g2->existProperty("metric"));
  CPPUNIT_ASSERT(!g3->existProperty("metric"));
  CPPUNIT_ASSERT(!g4->existProperty("metric"));


  QProperty *m2 = g2->getDoubleProperty("metric");
  CPPUNIT_ASSERT(!graph->existProperty("metric"));
  CPPUNIT_ASSERT(!g1->existProperty("metric"));
  CPPUNIT_ASSERT(g2->existProperty("metric"));
  CPPUNIT_ASSERT(g3->existProperty("metric"));
  CPPUNIT_ASSERT(g4->existProperty("metric"));

  m = graph->getDoubleProperty("metric");
  CPPUNIT_ASSERT(graph->getProperty("metric")->asProperty() == m->asProperty());
  CPPUNIT_ASSERT(g1->getProperty("metric")->asProperty() == m->asProperty());
  CPPUNIT_ASSERT(g2->getProperty("metric")->asProperty() == m2->asProperty());
  CPPUNIT_ASSERT(g3->getProperty("metric")->asProperty() == m2->asProperty());
  CPPUNIT_ASSERT(g4->getProperty("metric")->asProperty() == m2->asProperty());

  g2->delLocalProperty("metric");
  CPPUNIT_ASSERT(graph->getProperty("metric")->asProperty() == m->asProperty());
  CPPUNIT_ASSERT(g1->getProperty("metric")->asProperty() == m->asProperty());
  CPPUNIT_ASSERT(g2->getProperty("metric")->asProperty() == m->asProperty());
  CPPUNIT_ASSERT(g3->getProperty("metric")->asProperty() == m->asProperty());
  CPPUNIT_ASSERT(g4->getProperty("metric")->asProperty() == m->asProperty());

  graph->clear();
}
//==========================================================
void QGraphTest::testPropertiesIteration() {
  graph->clear();
  QGraph *g1, *g2, *g3, *g4;
  set<QString> propList1;
  set<QString> propList2;
  propList1.insert("m1");
  propList1.insert("m2");
  propList1.insert("m3");
  propList2.insert("m4");
  propList2.insert("m5");
  propList2.insert("m6");
  g1 = graph->addSubGraph();
  g2 = graph->addSubGraph();
  g3 = g2->addSubGraph();
  g4 = g2->addSubGraph();

  set<QString>::const_iterator it;
  for (it=propList1.begin();it!=propList1.end();++it) {
	  graph->getIntegerProperty(*it);
    CPPUNIT_ASSERT(g4->existProperty(*it));
  }
  QStringIterator *itS = graph->getProperties();
  while(itS->hasNext()) {
    CPPUNIT_ASSERT(propList1.find(itS->next())!=propList1.end());
  } delete itS;
  itS = g2->getProperties();
  while(itS->hasNext()) {
    CPPUNIT_ASSERT(propList1.find(itS->next())!=propList1.end());
  } delete itS;
  itS = g1->getLocalProperties();
  while(itS->hasNext()) {
    CPPUNIT_ASSERT(propList1.find(itS->next())==propList1.end());
  } delete itS;
  itS = g1->getLocalProperties();
  while(itS->hasNext()) {
    CPPUNIT_ASSERT(propList1.find(itS->next())==propList1.end());
  } delete itS;
  itS = g4->getInheritedProperties();
  while(itS->hasNext()) {
    CPPUNIT_ASSERT(propList1.find(itS->next())!=propList1.end());
  } delete itS;

  for (it=propList2.begin();it!=propList2.end();++it) {
    g2->getIntegerProperty(*it);
    CPPUNIT_ASSERT(g4->existProperty(*it));
  }

  itS = graph->getProperties();
  while(itS->hasNext()) {
    QString str = itS->next();
    CPPUNIT_ASSERT(propList1.find(str)!=propList1.end()  && propList2.find(str)==propList2.end());
  } delete itS;
  itS = g1->getProperties();
  while(itS->hasNext()) {
    QString str = itS->next();
    CPPUNIT_ASSERT(propList1.find(str)!=propList1.end()  && propList2.find(str)==propList2.end());
  } delete itS;
  itS = g2->getProperties();
  while(itS->hasNext()) {
    QString str = itS->next();
    CPPUNIT_ASSERT(propList1.find(str)!=propList1.end()  || propList2.find(str)!=propList2.end());
  } delete itS;
  itS = g3->getProperties();
  while(itS->hasNext()) {
    QString str = itS->next();
    CPPUNIT_ASSERT(propList1.find(str)!=propList1.end()  || propList2.find(str)!=propList2.end());
  } delete itS;
  itS = g4->getProperties();
  while(itS->hasNext()) {
    QString str = itS->next();
    CPPUNIT_ASSERT(propList1.find(str)!=propList1.end()  || propList2.find(str)!=propList2.end());
  } delete itS;
  graph->clear();
}
//==========================================================
