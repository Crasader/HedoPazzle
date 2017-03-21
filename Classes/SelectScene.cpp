#include "SelectScene.h"
#include "ui\CocosGUI.h"
#include "PlayScene.h"
using namespace cocos2d;
// �T�v�F������
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
	//// ���X�g�T�C�Y�ݒ�
	//listView->setContentSize(size);
	//// ���������̏���
	//listView->addEventListener(
	//	(ui::ListView::ccListViewCallback)
	//	[&](Ref * pSender, ui::ListView::EventType type) 
	//{
	//	//�^�b�`�I��������Ȃ��Ȃ�return
	//	if (type != ui::ListView::EventType::ON_SELECTED_ITEM_END)
	//		return;
	//	auto listView = static_cast<ui::ListView*>(pSender);
	//	// Stage��
	//	int stage = listView->getCurSelectedIndex() + 1;
	//	// PlayScene�ɐ؂�ւ�
	//	Director::getInstance()->replaceScene(HelloWorld::createScene());
	//});
	ui::Button* button = ui::Button::create("menu/select.png");
	button->setPosition(Vec2(200, 200));
	this->addChild(button);
	button->addTouchEventListener(
		[&](Ref * pSender, ui::Widget::TouchEventType type)
	{
		//�^�b�`�I��������Ȃ��Ȃ�return
		if (type != ui::Widget::TouchEventType::ENDED)
			return;		
		// PlayScene�ɐ؂�ւ�
		Director::getInstance()->replaceScene(PlayScene::createScene());
	});
	return true;
}
// �T�v�F�V�[���쐬
Scene * SelectScene::createScene()
{
	auto scene = Scene::create();
	auto layer = SelectScene::create();
	scene->addChild(layer);
	return scene;
}
