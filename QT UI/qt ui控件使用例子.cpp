/*
QTreeWidget例子:树形控件
*/
QTreeWidget *tree = new QTreeWidget;
    tree->setColumnCount(2);
    QStringList headers;
    headers << QObject::tr("科目") <<QObject::tr("分数");
    tree->setHeaderLabels(headers);

    QStringList zhangsan;
    zhangsan << QObject::tr("张三");
    QTreeWidgetItem *zhangsanroot = new QTreeWidgetItem(tree, zhangsan);
    QStringList zhangsanChinese;
    zhangsanChinese << QObject::tr("语文") << QObject::tr("80");
    QTreeWidgetItem *leaf1 = new QTreeWidgetItem(zhangsanroot, zhangsanChinese);
    zhangsanroot->addChild(leaf1);
    QStringList zhangsanMath;
    zhangsanMath << QObject::tr("数学") << QObject::tr("90");
    QTreeWidgetItem *leaf2 = new QTreeWidgetItem(zhangsanroot, zhangsanMath);
    zhangsanroot->addChild(leaf2);

    QStringList lisi;
    lisi << QObject::tr("李四");
    QTreeWidgetItem *lisiroot = new QTreeWidgetItem(tree, lisi);
    QStringList lisiChinese;
    lisiChinese << QObject::tr("语文") << QObject::tr("90");
    leaf1 = new QTreeWidgetItem(lisiroot, lisiChinese);
    lisiroot->addChild(leaf1);
    QStringList lisiMath;
    lisiMath << QObject::tr("数学") << QObject::tr("100");
    leaf2 = new QTreeWidgetItem(lisiroot, lisiMath);
    lisiroot->addChild(leaf2);

    tree->addTopLevelItem(zhangsanroot);
    tree->addTopLevelItem(lisiroot);

    QHBoxLayout *mainlayout = new QHBoxLayout;
    mainlayout->addWidget(tree);
    QWidget *widget = new QWidget;
    widget->setLayout(mainlayout);
    widget->show();