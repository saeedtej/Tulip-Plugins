#ifndef TESTOBSERVER_H
#define TESTOBSERVER_H

#include <cppunit/TestCase.h>
#include <cppunit/extensions/HelperMacros.h>

#include "../Observer.h"
#include "../Data.h"

class TestObservateur : public Observer
{
public:
	TestObservateur(Observable * obs):
		Observer(),
		_data(0)
	{
		obs->addObserver(this);
	}
	virtual void update(Observable * subject)
	{
		_data = ((Data *)subject)->size();
	}
	inline int getData() const { return _data; }
private:
	int _data;
};

class ObserverTest : public CppUnit::TestCase
{
  CPPUNIT_TEST_SUITE(ObserverTest);
      CPPUNIT_TEST(loadTest);
  CPPUNIT_TEST_SUITE_END();
private:
	IData<float> *_data;
	TestObservateur * _objetObservateur;
	Data * _donneeObservee;
public:
    void setUp()
    {
    	_donneeObservee = new Data;
		_objetObservateur = new TestObservateur(_donneeObservee);
    }

    void tearDown()
    {
    	delete _donneeObservee;
		delete _objetObservateur;
    }

protected:
    void loadTest()
    {
    	CPPUNIT_ASSERT_EQUAL(_objetObservateur->getData(), 0);
    	_donneeObservee->add(5, 2);
    	CPPUNIT_ASSERT_EQUAL(_objetObservateur->getData(), 1);
		_donneeObservee->add(8, 5);
    	CPPUNIT_ASSERT_EQUAL(_objetObservateur->getData(), 2);
    }
};

CPPUNIT_TEST_SUITE_REGISTRATION(ObserverTest);

#endif
