#include <QtTest>

#include "cursornavigationattached.h"
#include <QSignalSpy>
#include <QtQml/qqmlengine.h>
#include <QtQml/qqmlcomponent.h>
#include <QtQuick/qquickview.h>
#include <QtQuick/QQuickItem>
#include <QQmlProperty>

class TestCursorNavigation : public QObject
{
    Q_OBJECT

public:
    TestCursorNavigation();
    ~TestCursorNavigation();

private slots:
    void test_basics();
    void test_callbacks();
    void test_navigation4Directions();
    void test_navigation360();
    void testRedirects();
    void test_trapping();
    void test_targetDeletions();
};

TestCursorNavigation::TestCursorNavigation()
{

}

TestCursorNavigation::~TestCursorNavigation()
{

}



void TestCursorNavigation::test_basics()
{
    //test that the plugin loads and is available for use and a element with an attached property can be set
    QQuickView *view = new QQuickView;
    view->setSource(QUrl::fromLocalFile(QFINDTESTDATA("basics.qml")));
    QVERIFY(view->status() == QQuickView::Ready);

    view->show();
    view->requestActivate();

    QVERIFY(QTest::qWaitForWindowActive(view));
    QTRY_COMPARE(view, qGuiApp->focusWindow());

    QQuickItem *root = view->rootObject();
    QQuickItem *item0 = root->findChild<QQuickItem*>(QLatin1String("cnItem0"));
    QQuickItem *item1 = root->findChild<QQuickItem*>(QLatin1String("cnItem1"));
    QQuickItem *item2 = root->findChild<QQuickItem*>(QLatin1String("cnItem2"));
    QQuickItem *item1Child = root->findChild<QQuickItem*>(QLatin1String("cnItem1Child"));
    QQuickItem *item2IndirectChild = root->findChild<QQuickItem*>(QLatin1String("cnItem2IndirectChild"));
    QObject *item0Attached = item0->findChild<QObject*>(QLatin1String("cnItem0Attached"));
    QVERIFY(item0 != nullptr);
    QVERIFY(item1 != nullptr);
    QVERIFY(item0Attached != nullptr);

    //check initial property values
    QQmlProperty acceptsCursor0(item0, "CursorNavigation.acceptsCursor", qmlContext(item0));
    QQmlProperty hasCursor0(item0, "CursorNavigation.hasCursor", qmlContext(item0));
    QQmlProperty trapsCursor0(item0, "CursorNavigation.trapsCursor", qmlContext(item0));
    QQmlProperty escapeTarget0(item0, "CursorNavigation.escapeTarget", qmlContext(item0));
    QQmlProperty redirects0(item0, "CursorNavigation.redirects", qmlContext(item0));
    QVERIFY(acceptsCursor0.isValid());
    QVERIFY(hasCursor0.isValid());
    QVERIFY(trapsCursor0.isValid());
    QVERIFY(escapeTarget0.isValid());
    QVERIFY(redirects0.isValid());

    QVERIFY(!acceptsCursor0.read().toBool());
    QVERIFY(!hasCursor0.read().toBool());
    QVERIFY(!hasCursor0.read().toBool());
    QVERIFY(escapeTarget0.read().value<QQuickItem*>() == nullptr);
    //TODO check that redirects is empty

    QSignalSpy acceptsCursorSpy0(item0Attached, SIGNAL(acceptsCursorChanged(bool)));
    QSignalSpy hasCursorSpy0(item0Attached, SIGNAL(hasCursorChanged(bool)));

    acceptsCursor0.write(true);

    QVERIFY(acceptsCursorSpy0.count()==1);
    QVERIFY(acceptsCursor0.read().toBool());

    QVERIFY(view->isTopLevel());

    //check that cursor follows the active focus
    item0->forceActiveFocus();
    QVERIFY(item0->hasActiveFocus());
    QVERIFY(hasCursor0.read().toBool());
    QVERIFY(hasCursorSpy0.count()==1);


    //check, that when a non-navigable item receives the active focus, the cursor is set on its closest navigable parent
    QQmlProperty hasCursor1(item1, "CursorNavigation.hasCursor", qmlContext(item1));
    QVERIFY(!item1->hasActiveFocus());
    QVERIFY(!hasCursor1.read().toBool());

    item1Child->forceActiveFocus();
    //TODO this will not be true. should it be?
    //QVERIFY(item1Child->hasActiveFocus());
    QVERIFY(hasCursor1.read().toBool());

    QVERIFY(!hasCursor0.read().toBool());
    QVERIFY(hasCursorSpy0.count()==2);

    //...and the same with an indirect child
    QQmlProperty hasCursor2(item2, "CursorNavigation.hasCursor", qmlContext(item2));
    QVERIFY(!item2->hasActiveFocus());
    QVERIFY(!hasCursor2.read().toBool());

    item2IndirectChild->forceActiveFocus();
    //TODO this will not be true. should it be?
    //QVERIFY(item2IndirectChild->hasActiveFocus());
    QVERIFY(hasCursor2.read().toBool());

    delete view;
}

void TestCursorNavigation::test_callbacks()
{

}

void TestCursorNavigation::test_navigation4Directions()
{
    //test the spatial algorithm in the basic 4 directional case
    QQuickView *view = new QQuickView;
    view->setSource(QUrl::fromLocalFile(QFINDTESTDATA("4WayTest.qml")));
    QVERIFY(view->status() == QQuickView::Ready);

    view->show();
    view->requestActivate();

    QVERIFY(QTest::qWaitForWindowActive(view));
    QTRY_COMPARE(view, qGuiApp->focusWindow());

    QQuickItem *root = view->rootObject();
    QQuickItem *left = root->findChild<QQuickItem*>(QLatin1String("left"));
    QQuickItem *right = root->findChild<QQuickItem*>(QLatin1String("right"));
    QQuickItem *right1 = root->findChild<QQuickItem*>(QLatin1String("right1"));
    QQuickItem *right2 = root->findChild<QQuickItem*>(QLatin1String("right2"));
    QQuickItem *top = root->findChild<QQuickItem*>(QLatin1String("top"));
    QQuickItem *bottom = root->findChild<QQuickItem*>(QLatin1String("bottom"));
    QQuickItem *center = root->findChild<QQuickItem*>(QLatin1String("center"));

    QObject *leftAttached = left->findChild<QObject*>(QLatin1String("leftAttached"));

    QQmlProperty leftHasCursor(left, "CursorNavigation.hasCursor", qmlContext(left));
    QQmlProperty rightHasCursor(right, "CursorNavigation.hasCursor", qmlContext(right));
    QQmlProperty right1HasCursor(right1, "CursorNavigation.hasCursor", qmlContext(right1));
    QQmlProperty right2HasCursor(right2, "CursorNavigation.hasCursor", qmlContext(right2));
    QQmlProperty topHasCursor(top, "CursorNavigation.hasCursor", qmlContext(top));
    QQmlProperty bottomHasCursor(bottom, "CursorNavigation.hasCursor", qmlContext(bottom));
    QQmlProperty centerHasCursor(center, "CursorNavigation.hasCursor", qmlContext(center));


    /* test all directions with a direct target ie. in projection,
     * with the target being out of projection, and without any potential
     * target in that direction (a miss) */
    left->forceActiveFocus();
    QVERIFY(leftHasCursor.read().toBool());

    QMetaObject::invokeMethod(leftAttached, "moveLeft"); //miss
    QVERIFY(leftHasCursor.read().toBool());

    QMetaObject::invokeMethod(leftAttached, "moveRight");
    QVERIFY(centerHasCursor.read().toBool());

    QMetaObject::invokeMethod(leftAttached, "moveDown");
    QVERIFY(bottomHasCursor.read().toBool());

    QMetaObject::invokeMethod(leftAttached, "moveDown"); //miss
    QVERIFY(bottomHasCursor.read().toBool());

    QMetaObject::invokeMethod(leftAttached, "moveUp");
    QVERIFY(centerHasCursor.read().toBool());

    QMetaObject::invokeMethod(leftAttached, "moveRight");
    QVERIFY(rightHasCursor.read().toBool());

    //test that from 2 items within projection, the closest is picked
    QMetaObject::invokeMethod(leftAttached, "moveRight");
    QVERIFY(right1HasCursor.read().toBool());

    QMetaObject::invokeMethod(leftAttached, "moveRight"); //miss
    QVERIFY(right1HasCursor.read().toBool());

    QMetaObject::invokeMethod(leftAttached, "moveLeft");
    QMetaObject::invokeMethod(leftAttached, "moveLeft");
    QVERIFY(centerHasCursor.read().toBool());

    QMetaObject::invokeMethod(leftAttached, "moveUp");
    QVERIFY(topHasCursor.read().toBool());

    QMetaObject::invokeMethod(leftAttached, "moveUp"); //miss
    QVERIFY(topHasCursor.read().toBool());

    QMetaObject::invokeMethod(leftAttached, "moveDown");
    QVERIFY(centerHasCursor.read().toBool());

    QMetaObject::invokeMethod(leftAttached, "moveLeft");
    QVERIFY(leftHasCursor.read().toBool());

    //moves to item outside of projection
    QMetaObject::invokeMethod(leftAttached, "moveDown");
    QVERIFY(bottomHasCursor.read().toBool());

    QMetaObject::invokeMethod(leftAttached, "moveRight");
    QVERIFY(rightHasCursor.read().toBool());

    QMetaObject::invokeMethod(leftAttached, "moveUp");
    QVERIFY(topHasCursor.read().toBool());

    QMetaObject::invokeMethod(leftAttached, "moveLeft");
    QVERIFY(leftHasCursor.read().toBool());

    delete view;
}

void TestCursorNavigation::test_navigation360()
{

}

void TestCursorNavigation::testRedirects()
{

}

void TestCursorNavigation::test_trapping()
{

}

void TestCursorNavigation::test_targetDeletions()
{

}

QTEST_MAIN(TestCursorNavigation)

#include "tst_cursornavigation.moc"
