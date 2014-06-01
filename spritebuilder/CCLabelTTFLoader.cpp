#include "CCLabelTTFLoader.h"

using namespace cocos2d;

#define PROPERTY_BLENDFUNC "blendFunc"

#define PROPERTY_STRING "string"
#define PROPERTY_FONTNAME "fontName"
#define PROPERTY_FONTSIZE "fontSize"
#define PROPERTY_ADJUSTSFONTSIZETOFIT "adjustsFontSizeToFit" // TODO:
#define PROPERTY_OPACITY "opacity"
#define PROPERTY_COLOR "color"
#define PROPERTY_DIMENSIONS "dimensions"
#define PROPERTY_HORIZONTALALIGNMENT "horizontalAlignment"
#define PROPERTY_VERTICALALIGNMENT "verticalAlignment"
#define PROPERTY_FONTCOLOR "fontColor"
#define PROPERTY_OUTLINECOLOR "outlineColor"
#define PROPERTY_OUTLINEWIDTH "outlineWidth"
#define PROPERTY_SHADOWCOLOR "shadowColor"
#define PROPERTY_SHADOWBLURRADIUS "shadowBlurRadius"
#define PROPERTY_SHADOWOFFSET "shadowOffset"

namespace spritebuilder {
    
LabelTTFLoader::LabelTTFLoader() :
    NodeLoader(),
    _shadowOffset(Size(0,0)), _shadowBlurRadius(0), _shadowColor(Color4B::BLACK),
    _outlineColor(Color3B::BLACK), _outlineWidth(0)
{
}

void LabelTTFLoader::onHandlePropTypePosition(Node * pNode, Node * pParent, const char * pPropertyName, Point pPosition, CCBReader * ccbReader) {
	if(strcmp(pPropertyName, PROPERTY_SHADOWOFFSET) == 0) {
        this->_shadowOffset = Size(pPosition);
		((LabelTTF *)pNode)->enableShadow(this->_shadowOffset, this->_shadowColor.a/255.0f, this->_shadowBlurRadius, Color3B(this->_shadowColor));
    } else {
        NodeLoader::onHandlePropTypePosition(pNode, pParent, pPropertyName, pPosition, ccbReader);
    }
}

void LabelTTFLoader::onHandlePropTypeColor3(Node * pNode, Node * pParent, const char * pPropertyName, Color3B pColor3B, CCBReader * ccbReader) {
    if(strcmp(pPropertyName, PROPERTY_COLOR) == 0) {
        ((LabelTTF *)pNode)->setColor(pColor3B);
    } else {
        NodeLoader::onHandlePropTypeColor3(pNode, pParent, pPropertyName, pColor3B, ccbReader);
    }
}

void LabelTTFLoader::onHandlePropTypeColor4(Node * pNode, Node * pParent, const char * pPropertyName, Color4B pColor4B, CCBReader * ccbReader) {
    if(strcmp(pPropertyName, PROPERTY_FONTCOLOR) == 0) {
		((LabelTTF *)pNode)->setFontFillColor(Color3B(pColor4B));
        // TODO: with opacity
		((LabelTTF *)pNode)->setOpacity(pColor4B.a);
	} else if(strcmp(pPropertyName, PROPERTY_OUTLINECOLOR) == 0) {
        this->_outlineColor = Color3B(pColor4B);
		((LabelTTF *)pNode)->enableStroke(this->_outlineColor, this->_outlineWidth);
	} else if(strcmp(pPropertyName, PROPERTY_SHADOWCOLOR) == 0) {
        this->_shadowColor = pColor4B;
        ((LabelTTF *)pNode)->enableShadow(this->_shadowOffset, this->_shadowColor.a/255.0f, this->_shadowBlurRadius, Color3B(this->_shadowColor));
    } else {
        NodeLoader::onHandlePropTypeColor4(pNode, pParent, pPropertyName, pColor4B, ccbReader);
    }
}

void LabelTTFLoader::onHandlePropTypeByte(Node * pNode, Node * pParent, const char * pPropertyName, unsigned char pByte, CCBReader * ccbReader) {
    if(strcmp(pPropertyName, PROPERTY_OPACITY) == 0) {
        // TODO: with fontcolor
        ((LabelTTF *)pNode)->setOpacity(pByte);
    } else {
        NodeLoader::onHandlePropTypeByte(pNode, pParent, pPropertyName, pByte, ccbReader);
    }
}

void LabelTTFLoader::onHandlePropTypeBlendFunc(Node * pNode, Node * pParent, const char * pPropertyName, BlendFunc pBlendFunc, CCBReader * ccbReader) {
    if(strcmp(pPropertyName, PROPERTY_BLENDFUNC) == 0) {
        ((LabelTTF *)pNode)->setBlendFunc(pBlendFunc);
    } else {
        NodeLoader::onHandlePropTypeBlendFunc(pNode, pParent, pPropertyName, pBlendFunc, ccbReader);
    }
}

void LabelTTFLoader::onHandlePropTypeFontTTF(Node * pNode, Node * pParent, const char * pPropertyName, const char * pFontTTF, CCBReader * ccbReader) {
    if(strcmp(pPropertyName, PROPERTY_FONTNAME) == 0) {
        ((LabelTTF *)pNode)->setFontName(pFontTTF);
    } else {
        NodeLoader::onHandlePropTypeFontTTF(pNode, pParent, pPropertyName, pFontTTF, ccbReader);
    }
}

void LabelTTFLoader::onHandlePropTypeText(Node * pNode, Node * pParent, const char * pPropertyName, const char * pText, CCBReader * ccbReader) {
    if(strcmp(pPropertyName, PROPERTY_STRING) == 0) {
        ((LabelTTF *)pNode)->setString(pText);
    } else {
        NodeLoader::onHandlePropTypeText(pNode, pParent, pPropertyName, pText, ccbReader);
    }
}

void LabelTTFLoader::onHandlePropTypeFloatScale(Node * pNode, Node * pParent, const char * pPropertyName, float pFloatScale, CCBReader * ccbReader) {
    if(strcmp(pPropertyName, PROPERTY_FONTSIZE) == 0) {
        ((LabelTTF *)pNode)->setFontSize(pFloatScale);
	} else if(strcmp(pPropertyName, PROPERTY_OUTLINEWIDTH) == 0) {
        this->_outlineWidth = pFloatScale;
		((LabelTTF *)pNode)->enableStroke(this->_outlineColor, this->_outlineWidth);
	} else if(strcmp(pPropertyName, PROPERTY_SHADOWBLURRADIUS) == 0) {
        this->_shadowBlurRadius = pFloatScale;
        ((LabelTTF *)pNode)->enableShadow(this->_shadowOffset, this->_shadowColor.a/255.0f, this->_shadowBlurRadius, Color3B(this->_shadowColor));
    } else {
        NodeLoader::onHandlePropTypeFloatScale(pNode, pParent, pPropertyName, pFloatScale, ccbReader);
    }
}

void LabelTTFLoader::onHandlePropTypeIntegerLabeled(Node * pNode, Node * pParent, const char * pPropertyName, int pIntegerLabeled, CCBReader * ccbReader) {
    if(strcmp(pPropertyName, PROPERTY_HORIZONTALALIGNMENT) == 0) {
        ((LabelTTF *)pNode)->setHorizontalAlignment(TextHAlignment(pIntegerLabeled));
    } else if(strcmp(pPropertyName, PROPERTY_VERTICALALIGNMENT) == 0) {
        ((LabelTTF *)pNode)->setVerticalAlignment(TextVAlignment(pIntegerLabeled));
    } else {
        NodeLoader::onHandlePropTypeFloatScale(pNode, pParent, pPropertyName, pIntegerLabeled, ccbReader);
    }
}

void LabelTTFLoader::onHandlePropTypeSize(Node * pNode, Node * pParent, const char * pPropertyName, Size pSize, CCBReader * ccbReader) {
    if(strcmp(pPropertyName, PROPERTY_DIMENSIONS) == 0) {
        ((LabelTTF *)pNode)->setDimensions(pSize);
    } else {
        NodeLoader::onHandlePropTypeSize(pNode, pParent, pPropertyName, pSize, ccbReader);
    }
}

}