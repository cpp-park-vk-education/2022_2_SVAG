#include "menu.h"

QWidget *Navbar::Draw() const {
  // Navbar //
  QWidget *navbarWidget = new QWidget();
  navbarWidget->setObjectName("navbarWidget");
  navbarWidget->setMinimumSize(QSize(600, 35));
  navbarWidget->setMaximumSize(QSize(2000, 35));
  navbarWidget->setContentsMargins(0, 0, 0, 0);

  QHBoxLayout *navbarLayout = new QHBoxLayout(navbarWidget);
  navbarLayout->setObjectName("navbarLayout");
  navbarLayout->setContentsMargins(10, 0, 10, 0);
  navbarLayout->setSpacing(0);
  // Navbar //

  QLabel *programmIcon = new QLabel(navbarWidget);
  programmIcon->setObjectName("programmIcon");
  programmIcon->setMinimumSize(QSize(30, 30));
  programmIcon->setMaximumSize(QSize(30, 30));

  navbarLayout->addWidget(programmIcon);

  QLabel *programmName = new QLabel(QObject::tr("DoIT"), navbarWidget);
  programmName->setObjectName("programmName");
  programmName->setMinimumSize(QSize(50, 30));
  programmName->setMaximumSize(QSize(100, 30));

  navbarLayout->addWidget(programmName);

  QComboBox *chooseBoard = new QComboBox(navbarWidget);
  chooseBoard->setObjectName("chooseBoard");
  chooseBoard->setMinimumSize(QSize(200, 30));
  chooseBoard->setMaximumSize(QSize(200, 30));
  chooseBoard->setCursor(QCursor(Qt::PointingHandCursor));

  navbarLayout->addWidget(chooseBoard);

  QSpacerItem *spacer_1 =
      new QSpacerItem(10, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

  navbarLayout->addItem(spacer_1);

  QPushButton *createBoard =
      new QPushButton(QObject::tr("Создать"), navbarWidget);
  createBoard->setObjectName("createBoard");
  createBoard->setMinimumSize(QSize(100, 30));
  createBoard->setMaximumSize(QSize(100, 30));
  createBoard->setCursor(QCursor(Qt::PointingHandCursor));

  navbarLayout->addWidget(createBoard);

  QSpacerItem *spacer_2 =
      new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

  navbarLayout->addItem(spacer_2);

  QComboBox *userSettings = new QComboBox(navbarWidget);
  userSettings->setObjectName("userSettings");
  userSettings->setMinimumSize(QSize(30, 30));
  userSettings->setMaximumSize(QSize(30, 30));
  userSettings->setCursor(QCursor(Qt::PointingHandCursor));

  navbarLayout->addWidget(userSettings);

  // Styles //
  navbarWidget->setStyleSheet(QString::fromUtf8(
      "#programmIcon {\n"
      "  image: url(Gui/resources/icons/logo.jpg);\n"
      "  width: 20px;\n"
      "  min-height: 20px;\n"
      "}\n"
      "\n"
      "#programmName {\n"
      "  font: bold 24px;\n"
      "  font-style: italic;\n"
      "\n"
      "  margin-right: 30px;\n"
      "}\n"
      "\n"
      "#navbarWidget {\n"
      "  background-color: hsl(194, 17%, 30.9%);\n"
      "  margin: 0px 0px;\n"
      "}\n"
      "\n"
      "#navbarWidget > * {\n"
      "   border-radius: 5px;\n"
      "}\n"
      "\n"
      "#chooseBoard {\n"
      "  background: transparent;\n"
      "  color: black;\n"
      "  padding-left: 5px;\n"
      "}\n"
      "\n"
      "#chooseBoard:hover {\n"
      "  background-color: hsl(194, 4%, 53%);\n"
      "}\n"
      "\n"
      "#chooseBoard::drop-down {\n"
      "   subcontrol-origin: padding;\n"
      "   subcontrol-position: top right;\n"
      "\n"
      "   border-top-right-radius: 5px;\n"
      "   border-bottom-right-radius: 5px;\n"
      "\n"
      "  padding-right: 10px;\n"
      "}\n"
      "\n"
      "#chooseBoard::down-arrow {\n"
      "   image: url(Gui/resources/icons/arrow.png);\n"
      "  width: 20px;\n"
      "  min-height: 20px;\n"
      "}\n"
      "\n"
      "#chooseBoard::down-arrow:on {\n"
      "   top: 2px;\n"
      "}\n"
      "\n"
      "#chooseBoard QListView {\n"
      "  padding: 5px;\n"
      "  background-color: white;\n"
      "   border-radius: 5px;\n"
      "   outline: 0px;\n"
      "}\n"
      "\n"
      "#chooseBoard QListView::item {\n"
      "   height: 30px;\n"
      "}\n"
      "\n"
      "#chooseBoard QListView::item:focus, #chooseBoard "
      "QListView::item:hover, #chooseBoard QListView::item:selected {\n"
      "  color: black;\n"
      "  background-color: silver;\n"
      "}\n"
      "\n"
      "#createBoard {\n"
      "  background-color:  hsl(194, 4%, 53%);\n"
      "}\n"
      "\n"
      "#createBoard:hover {\n"
      "  background-color: hsl(194, 10%, 60%);\n"
      "}\n"
      "\n"
      "#userSettings {\n"
      "  background: transparent;\n"
      "  image: url(Gui/resources/icons/default_user.png);\n"
      "}\n"
      "\n"
      "#userSettings::drop-down {\n"
      "  border: 0px;\n"
      "}\n"
      "\n"
      "#userSettings QListView {\n"
      "  min-width: 100px;\n"
      "  background-color: white;\n"
      "}\n"
      "\n"
      "#userSettings QListView::item {\n"
      "  width: 100px;\n"
      "    height: 30px;\n"
      "}\n"
      "\n"
      "#userSettings QListView::item:focus, #userSettings "
      "QListView::item:hover {\n"
      "  color: black;\n"
      "  background-color: silver;\n"
      "}\n"
      ""));

  return navbarWidget;
}

QWidget *Menu::Draw() const {
  // Menu //
  QWidget *menuWidget = new QWidget();
  menuWidget->setObjectName("menuWidget");
  menuWidget->setMinimumSize(QSize(200, 500));
  menuWidget->setMaximumSize(QSize(200, 2000));
  menuWidget->setContentsMargins(0, 0, 0, 0);

  QVBoxLayout *menuLayout = new QVBoxLayout(menuWidget);
  menuLayout->setObjectName("menuLayout");
  menuLayout->setContentsMargins(0, 0, 0, 0);
  menuLayout->setSpacing(0);

  // Row 1
  QWidget *rowWidget_1 = new QWidget();
  rowWidget_1->setObjectName("rowWidget_1");
  rowWidget_1->setMinimumSize(QSize(100, 40));
  rowWidget_1->setContentsMargins(0, 0, 0, 0);

  QHBoxLayout *rowLayout_1 = new QHBoxLayout(rowWidget_1);
  rowLayout_1->setObjectName("rowLayout_1");
  rowLayout_1->setContentsMargins(0, 0, 0, 0);
  rowLayout_1->setSpacing(0);

  // Row 1 Content
  QLabel *actionsText = new QLabel(QObject::tr("Действия"));
  actionsText->setObjectName("actionsText");
  actionsText->setMinimumSize(QSize(100, 40));
  actionsText->setAlignment(Qt::AlignCenter);

  // Add
  rowLayout_1->addWidget(actionsText);

  menuLayout->addWidget(rowWidget_1);

  // Line
  QFrame *line = new QFrame();
  line->setFrameShape(QFrame::HLine); // Horizontal line
  line->setFrameShadow(QFrame::Sunken);
  line->setLineWidth(1);

  // Add Line
  menuLayout->addWidget(line);

  // Row 2
  QWidget *rowWidget_2 = new QWidget();
  rowWidget_2->setObjectName("rowWidget_2");
  rowWidget_2->setMinimumSize(QSize(100, 30));
  rowWidget_2->setCursor(QCursor(Qt::PointingHandCursor));
  rowWidget_2->setContentsMargins(0, 0, 0, 0);

  QHBoxLayout *rowLayout_2 = new QHBoxLayout(rowWidget_2);
  rowLayout_2->setObjectName("rowLayout_2");
  rowLayout_2->setContentsMargins(0, 0, 0, 0);
  rowLayout_2->setSpacing(0);

  // Row 2 Content
  QLabel *avatarIcon = new QLabel();
  avatarIcon->setObjectName("avatarIcon");
  avatarIcon->setMinimumSize(QSize(30, 30));
  avatarIcon->setMaximumSize(QSize(30, 30));
  avatarIcon->setCursor(QCursor(Qt::PointingHandCursor));

  QLabel *usersText = new QLabel(QObject::tr("Участники"));
  usersText->setObjectName("usersText");
  usersText->setMinimumSize(QSize(100, 30));
  usersText->setMaximumSize(QSize(200, 30));
  usersText->setCursor(QCursor(Qt::PointingHandCursor));

  QLabel *addAvatarIcon = new QLabel();
  addAvatarIcon->setObjectName("addAvatarIcon");
  addAvatarIcon->setMinimumSize(QSize(30, 30));
  addAvatarIcon->setMaximumSize(QSize(30, 30));
  addAvatarIcon->setCursor(QCursor(Qt::PointingHandCursor));

  // Add
  rowLayout_2->addWidget(avatarIcon);
  rowLayout_2->addWidget(usersText);
  rowLayout_2->addWidget(addAvatarIcon);

  menuLayout->addWidget(rowWidget_2);

  // Spacer at the end
  QSpacerItem *bMenuSpacer =
      new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

  menuLayout->addItem(bMenuSpacer);

  // Styles //
  menuWidget->setStyleSheet(QString::fromUtf8(
      "#menuWidget {\n"
      "	background-color: hsla(194,17%,35.9%,0.9);\n"
      "}\n"
      "\n"
      "#menuWidget > * > * {\n"
      "	color: white;\n"
      "    border-radius: 5px;\n"
      "}\n"
      "\n"
      "#actionsText {\n"
      "	font: bold 18px;\n"
      "	font-style: italic;\n"
      "}\n"
      "\n"
      "#usersText {\n"
      "	font: bold 14px;\n"
      "	padding-left: 10px;\n"
      "}\n"
      "\n"
      "#avatarIcon {\n"
      "	background: transparent;\n"
      "	image: url(Gui/resources/icons/user_white.png);\n"
      "	margin-left: 5px;\n"
      "}\n"
      "\n"
      "#addAvatarIcon {\n"
      "	background: transparent;\n"
      "	image: url(Gui/resources/icons/plus_white.png);\n"
      "	margin-right: 10px;\n"
      "}\n"
      "\n"
      "#rowWidget_2:hover {\n"
      "	background-color: hsl(194, 4%, 53%);\n"
      "}\n"
      ""));

  return menuWidget;
}
