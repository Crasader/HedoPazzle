#include "MenuList.h"
#include "PlayScene.h"
#include "SelectScene.h"
#include "AudioEngine.h"
using namespace cocos2d;
const float speed = 0.2f;
// �T�v�F������
bool MenuList::init()
{
	if (!Node::init())
		return false;
	// �F�̐ݒ�
	m_color = LayerColor::create();
	this->addChild(m_color);
	// ���X�g���J���{�^��
	m_button = ui::Button::create("menu/menu.png");
	// �^�b�`���̏���
	m_button->addTouchEventListener(
		CC_CALLBACK_2(MenuList::touchEvent, this));
	this->addChild(m_button);
	return true;
}
// �T�v�F�ڕW�ʒu
// �����F�����ʒufalse�A���S�ʒutrue
cocos2d::Vec2 MenuList::getTargetPosition(bool target)const
{
	// ��ʃT�C�Y�擾
	Size screen_size = Director::getInstance()->getVisibleSize() / 2;
	// ���X�g�T�C�Y�擾
	Size list_size = m_listView->getContentSize() / 2;
	// ���S�ʒu
	Vec2 position = screen_size - list_size;
	// �����ʒu�Ȃ�
	if (target == false) position.x *= -1;
	return position;
}
// �T�v�F���X�g����
void MenuList::createListView()
{
	m_listView = ui::ListView::create();
	// �{�^�����m�̊Ԋu
	m_listView->setItemsMargin(20.0f);
	this->addChild(m_listView);
	Size size;
	float margin = m_listView->getItemsMargin();
	for (int i = 0; i < ALL; i++)
	{
		char s[32];
		if (i == SELECT)sprintf(s, "menu/select.png");
		else if (i == RESET)sprintf(s, "menu/reset.png");
		ui::Button* button = ui::Button::create(s);
		Vec2 pos = button->getContentSize() / 2 + Size(margin, -margin);
		button->setPosition(pos);
		auto layout = ui::Layout::create();
		layout->setContentSize(button->getContentSize());
		layout->addChild(button);
		m_listView->addChild(layout);
		size.width = button->getContentSize().width + margin * 2;
		size.height += button->getContentSize().height + margin;
	}
	// ���X�g�T�C�Y�ݒ�
	m_listView->setContentSize(size);
	//�����n�_
	m_listView->setPosition(getTargetPosition(false));
	m_listView->setDirection(ui::ScrollView::Direction::VERTICAL);
	m_listView->setBounceEnabled(false);
	m_listView->setScrollBarEnabled(false);
	m_listView->addEventListener((ui::ListView::ccListViewCallback)
		CC_CALLBACK_2(MenuList::selectedItemEvent, this));
}
// �T�v�F���X�g�ړ��J�n����
void MenuList::BeginListView()
{
	// ��ʂ��Â�����
	m_color->initWithColor(
		Color4B(0x00, 0x00, 0x00, 0xff));
	m_color->setOpacity(100);
	cocos2d::Node* parent = this->getParent();
	this->pauseRecursive(parent, true);
	this->pauseRecursive(this, false);
	// ���X�g����
	createListView();
	// ���S�Ɏ����Ă�
	MoveTo* move = MoveTo::create(speed, getTargetPosition(true));
	m_listView->runAction(move);
}
// �T�v�F���X�g�ړ��I������
void MenuList::EndListView()
{
	// ��ʂ𖾂邭����
	m_color->initWithColor(
		Color4B(0x00, 0x00, 0x00, 0x00));
	cocos2d::Node* parent = this->getParent();
	this->pauseRecursive(parent, false);
	// �����ʒu�ɖ߂�
	MoveTo* move = MoveTo::create(speed, getTargetPosition(false));
	RemoveSelf* re = RemoveSelf::create();
	CallFunc* func = CallFunc::create([this](){m_listView = nullptr;});
	Sequence* seq = Sequence::create(move, re, func, nullptr);
	m_listView->runAction(seq);
}
// �T�v�F�e�q�֌W�S�Ă��@pause,resume
void MenuList::pauseRecursive(Node* node, bool pause)
{
	if (pause)
		node->pause();
	else
		node->resume();
	Ref* child = nullptr;
	auto& children = node->getChildren();
	for (size_t i = 0; i < children.size(); i++)
		pauseRecursive(children.at(i), pause);	
}
// �T�v�F�{�^���̏���
void MenuList::touchEvent(
	Ref * pSender, ui::Widget::TouchEventType type)
{
	// �^�b�`�I��������Ȃ��Ȃ�return
	if (type != ui::Widget::TouchEventType::ENDED)
		return;	
	experimental::AudioEngine::play2d("button.mp3");
	// ���X�g�ړ�����
	if (m_listView)
	{
		// �A�N�V�������ĂȂ��Ȃ�
		if (m_listView->numberOfRunningActions() == 0)
			EndListView();		
	}	
	else BeginListView();	
}
// �T�v�F���X�g�̃{�^������
void MenuList::selectedItemEvent(
	Ref * pSender, ui::ListView::EventType type)
{
	// �^�b�`�I��������Ȃ��Ȃ�return
	if (type != ui::ListView::EventType::ON_SELECTED_ITEM_END)
		return;
	experimental::AudioEngine::stopAll();
	experimental::AudioEngine::play2d("button.mp3");
	auto listView = static_cast<ui::ListView*>(pSender);
	switch (listView->getCurSelectedIndex())
	{
	case SELECT:
		Director::getInstance()->replaceScene(
			SelectScene::createScene());
		break;
	case RESET:
		Director::getInstance()->replaceScene(
			PlayScene::createScene());
		break;
	default: assert(false); break;
	}
}
