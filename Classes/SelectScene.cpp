#include "SelectScene.h"
#include "ui\CocosGUI.h"
#include "PlayScene.h"
using namespace cocos2d;
// 概要：初期化
bool SelectScene::init()
{
	if (!Layer::init())
		return false;
	//Vec2 pos = Director::getInstance()->getVisibleSize()/2;
	//auto listView = ui::ListView::create();
	//listView->setPosition(pos);
	//listView->setItemsMargin(20.0f);
	//this->addChild(listView);
	//Size size;
	//float margin = listView->getItemsMargin();
	//for (int i = 0; i < 4; i++)
	//{
	//	auto button = ui::Button::create("menu/select.png");
	//	auto layout = ui::Layout::create();
	//	layout->setContentSize(button->getContentSize());
	//	layout->addChild(button);
	//	listView->addChild(layout);
	//	size.width = button->getContentSize().width/* + margin * 2*/;
	//	size.height += button->getContentSize().height + margin;
	//}
	//// リストサイズ設定
	//listView->setContentSize(size);
	//// 押した時の処理
	//listView->addEventListener(
	//	(ui::ListView::ccListViewCallback)
	//	[&](Ref * pSender, ui::ListView::EventType type) 
	//{
	//	//タッチ終了時じゃないならreturn
	//	if (type != ui::ListView::EventType::ON_SELECTED_ITEM_END)
	//		return;
	//	auto listView = static_cast<ui::ListView*>(pSender);
	//	// Stage数
	//	int stage = listView->getCurSelectedIndex() + 1;
	//	// PlaySceneに切り替え
	//	Director::getInstance()->replaceScene(HelloWorld::createScene());
	//});
	ui::Button* button = ui::Button::create("menu/select.png");
	button->setPosition(Vec2(200, 200));
	this->addChild(button);
	button->addTouchEventListener(
		[&](Ref * pSender, ui::Widget::TouchEventType type)
	{
		//タッチ終了時じゃないならreturn
		if (type != ui::Widget::TouchEventType::ENDED)
			return;		
		// PlaySceneに切り替え
		Director::getInstance()->replaceScene(PlayScene::createScene());
	});
	return true;
}
// 概要：シーン作成
Scene * SelectScene::createScene()
{
	auto scene = Scene::create();
	auto layer = SelectScene::create();
	scene->addChild(layer);
	return scene;
}
