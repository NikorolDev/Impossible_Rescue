#ifndef OPENINGSCENE_H
#define OPENINGSCENE_H

#include "AudioEngine.h"
#include "cocos2d.h"

class CSceneManager;

USING_NS_CC;

class COpeningScene : public Scene
{
private:
	cocos2d::Sprite* m_pcBackground;
	cocos2d::Sprite* m_pcName;

	CSceneManager* m_pcSceneManager;

public:
	COpeningScene();
	~COpeningScene();

	//-----------------------------------------------------------------------------------------------------------------------------
	// Function Name	: init()
	// Author			: cocos2dx
	// Editors			: None
	// Parameters		: init
	// Purpose			: This super function is called when the scene is created.
	// Returns			: None
	// Example File		:
	// Example Usage	: 
	//-----------------------------------------------------------------------------------------------------------------------------
	virtual bool init();

	void Initialise(CSceneManager* pcSceneManager);

	void CreateBackground();

	void CreateAction();

	CREATE_FUNC( COpeningScene );
};

#endif // OPENINGSCENE_H