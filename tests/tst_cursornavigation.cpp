#include <QtTest>

// add necessary includes here

class TestCursorNavigation : public QObject
{
    Q_OBJECT

public:
    TestCursorNavigation();
    ~TestCursorNavigation();

private slots:
    void test_pluginLoading();
    void test_registering();
    void test_followsFocus();
    void test_withKeyNavigation();
    void test_spatial4Directions();

};

TestCursorNavigation::TestCursorNavigation()
{

}

TestCursorNavigation::~TestCursorNavigation()
{

}

void TestCursorNavigation::test_pluginLoading()
{
    //test that the plugin loads and is available for use and a element with an attached property can be set
}

void TestCursorNavigation::test_registering()
{
    //see that elements marked for accepting cursor are added to the engines element register
    //adding the property should add item to the register
    //deleting the item should unregister the item
    //unsetting the property should unregister the item
}

void TestCursorNavigation::test_followsFocus()
{
    //test that the cursor follows focus; means cursor is moved between the
    //items when the focus is changed some other way
}

void TestCursorNavigation::test_withKeyNavigation()
{
    //test that element that additionally uses KeyNavigation, behaves primarily according to the KeyNavigation
    //ie Cursor navigation plugin should not override KeyNavigation
    //arrows + tab/backtab
}

void TestCursorNavigation::test_spatial4Directions()
{
    //test the spatial algorithm in the basic 4 directional case
}

QTEST_APPLESS_MAIN(TestCursorNavigation)

#include "tst_cursornavigation.moc"
