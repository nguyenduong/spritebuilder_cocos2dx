#include "CCTextFieldLoader.h"

using namespace cocos2d;
using namespace cocos2d::extension;

#define PROPERTY_PREFERREDSIZE "preferredSize"
#define PROPERTY_SPRITEFRAME "backgroundSpriteFrame"
#define PROPERTY_PADDING "padding"
#define PROPERTY_BLOCK "block"

namespace spritebuilder {

    class ExtTextField : public EditBox, public cocos2d::extension::EditBoxDelegate {

    public:
        ExtTextField():_target(NULL), mSELControlHandler(NULL) {
            
        }
        virtual void editBoxEditingDidBegin(cocos2d::extension::EditBox* editBox) {
            
        }
        virtual void editBoxEditingDidEnd(cocos2d::extension::EditBox* editBox) {
            
        }
        virtual void editBoxTextChanged(cocos2d::extension::EditBox* editBox, const std::string& text) {
            
        }
        virtual void editBoxReturn(cocos2d::extension::EditBox* editBox) {
            if (_target && mSELControlHandler)
                (_target->*mSELControlHandler)(this, cocos2d::extension::Control::EventType::DRAG_EXIT);
        }
        void setTargetSelector(Ref* target, cocos2d::extension::Control::Handler handler) {
            _target = target;
            mSELControlHandler = handler;
        }
    private:
        Ref* _target;
        cocos2d::extension::Control::Handler mSELControlHandler;
        
    };
 

cocos2d::extension::EditBox * EditBoxLoader::createNode(cocos2d::Node * pParent, CCBReader * ccbReader) {
    ExtTextField* pRet = new ExtTextField();
    pRet->initWithSizeAndBackgroundSprite(cocos2d::Size(0,0), cocos2d::extension::Scale9Sprite::create());
    pRet->autorelease();
    pRet->setDelegate(pRet);
    pRet->setFontName("Helvetica");
    pRet->setFontColor(cocos2d::Color3B::BLACK);
        
    return pRet;
}


void EditBoxLoader::onHandlePropTypeSize(Node * pNode, Node * pParent, const char* pPropertyName, Size pSize, CCBReader * ccbReader) {
    if(strcmp(pPropertyName, PROPERTY_PREFERREDSIZE) == 0) {
        ((EditBox*)pNode)->setPreferredSize(pSize);
        ((EditBox*)pNode)->setFontSize(pSize.height*2/3);
    } else {
        ControlLoader::onHandlePropTypeSize(pNode, pParent, pPropertyName, pSize, ccbReader);
    }
}

void EditBoxLoader::onHandlePropTypeSpriteFrame(Node * pNode, Node * pParent, const char * pPropertyName, SpriteFrame * pSpriteFrame, CCBReader * ccbReader) {
    if(strcmp(pPropertyName, PROPERTY_SPRITEFRAME) == 0) {
        ((EditBox*)pNode)->setBackgroundSpriteFrameForState(pSpriteFrame, Control::State::NORMAL);
    } else {
        ControlLoader::onHandlePropTypeSpriteFrame(pNode, pParent, pPropertyName, pSpriteFrame, ccbReader);
    }
}

void EditBoxLoader::onHandlePropTypeFloatScale(Node * pNode, Node * pParent, const char* pPropertyName, float pFloatScale, CCBReader * ccbReader) {
    if(strcmp(pPropertyName, PROPERTY_PADDING) == 0) {
    } else {
        ControlLoader::onHandlePropTypeFloatScale(pNode, pParent, pPropertyName, pFloatScale, ccbReader);
    }
}
void EditBoxLoader::onHandlePropTypeBlockControl(Node * pNode, Node * pParent, const char * pPropertyName, BlockControlData * pBlockControlData, CCBReader * ccbReader) {
    if(strcmp(pPropertyName, PROPERTY_BLOCK) == 0) {
            ((ExtTextField*)pNode)->setTargetSelector(pBlockControlData->_target, pBlockControlData->mSELControlHandler);
    } else {
            ControlLoader::onHandlePropTypeBlockControl(pNode, pParent, pPropertyName, pBlockControlData, ccbReader);
    }
}

};