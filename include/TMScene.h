/*
*   Copyright (C) {2019.1}  {Djunio - SeiTbNao - Wed}
*
*   This program is free software: you can redistribute it and/or modify
*   it under the terms of the GNU General Public License as published by
*   the Free Software Foundation, either version 3 of the License, or
*   (at your option) any later version.
*
*   This program is distributed in the hope that it will be useful,
*   but WITHOUT ANY WARRANTY; without even the implied warranty of
*   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*   GNU General Public License for more details.
*
*   You should have received a copy of the GNU General Public License
*   along with this program.  If not, see [http://www.gnu.org/licenses/].
*
*/ 
 
class TMScene : public TreeNode
{
public:
	int Scene;
	TreeNode* GameInstance;
	TreeNode* TMEffect;	  
	TreeNode* Unk;			 
	TreeNode* Unk2;		 
	TreeNode* TMItem;		 
	TreeNode* TMFont3;
	TreeNode* unk4;
	TreeNode* unk5;
	TreeNode* unk6;
	TreeNode* TMHuman;
	char Unknown_0x002C[8];
	TreeNode* pInterface10;
	TreeNode* pInterface11;
    TreeNode* pInterface12;
	TreeNode* pInterface13;
    TreeNode* pInterface14;	
	char Unknown_0x002D[4];
	TreeNode* pInterface15;	
	char Unknown_0x002E[16];
	TreeNode* pInterface16;	
	TreeNode* pInterface17;	
	TreeNode* pInterface18;
	TreeNode* pInterface19;
	char unks[46];
	TreeNode* pClientMenssage;
	TreeNode* pInterface20;
	TreeNode* pMenssageBox;
public:
	// Singleton
	static TMScene* Instance()
	{
		PDWORD g_pGameClass = (PDWORD)ClientAddresses::Memory::TMScene;
		return *g_pGameClass ? (TMScene*)(*g_pGameClass) : nullptr;
	}


public:
	int getFieldScene()
	{
		if (!this || !this->getTMScene())
			return 0;

		// by SeiTbNao
		//----- (00499EC2) --------------------------------------------------------
		static DWORD rtnValue = 0;
		__asm {
			MOV EAX, CLIENT_ADDR_TM_SCENE
			MOV EDX, DWORD PTR DS : [EAX]
			MOV ECX, EDX
			MOV EAX, CLIENT_RAW_00499EC2
			CALL EAX//Scene Atual
			MOV rtnValue, EAX
		}
		return rtnValue;
	}

	
	//----- (0040409E) --------------------------------------------------------
	int  ShowClientMsg(const char* str)
	{
		if (!this || !str)
			return 0;

		auto clientMessage = *(DWORD*)(reinterpret_cast<DWORD>(this) + 196);
		if (!clientMessage)
			return 0;

		return callThiscall(ClientAddresses::Function::ClientMessageShow, int, TreeNode*, const char*, int)(reinterpret_cast<TreeNode*>(clientMessage), str, 3000);

	}

	void ShowExpMsg(DWORD Color, const char* Message, ...)
	{
		if (!this || !Message)
			return;

		static char buffer[128] = { 0, };
		va_list va;
		va_start(va, Message);
		int size = vsprintf_s(buffer, Message, va);

		if (size >= sizeof buffer || size == -1)
			return;

		va_end(va);


		auto control = this->FindControl<SListBox>(65944);

		if (!control)
			return;
		control->clear();
		auto text = SListBox::CreateSelectionLabel(buffer, Color);
		if (text)
			control->add(text);
	}

	void setFocus(SEditableText* editbox)
	{
		if (!this || !editbox)
			return;

		auto interfacePtr = *(DWORD*)(reinterpret_cast<DWORD>(this) + 40);
		if (!interfacePtr || !*(DWORD*)interfacePtr)
			return;

		return (*(void(__thiscall**)(DWORD, SEditableText*))(*(DWORD*)interfacePtr + 64))(interfacePtr, editbox);
	}

	//Adiciona Uma class na lista, usado para criar componentes ingame
	int  AddElement(TreeNode* Componente)
	{//att
		if (!this || !Componente)
			return 0;

		return callThiscall(ClientAddresses::Function::TreeNodeAttach, int, TMScene*, TreeNode*)(this, Componente);
	}
	int  addEffect(TreeNode* element)
	{//att
		if (!this || !this->TMEffect || !element)
			return 0;

		return callThiscall(ClientAddresses::Function::TreeNodeAttach, int, TreeNode*, TreeNode*)(this->TMEffect, element);
	}
	int addTMFont3(TreeNode* element)
	{//att
		if (!this || !this->TMFont3 || !element)
			return 0;

		return callThiscall(ClientAddresses::Function::TreeNodeAttach, int, TreeNode*, TreeNode*)(this->TMFont3, element);
	}	
	int addTMHuman(TreeNode* element)
	{//att
		if (!this || !this->TMHuman || !element)
			return 0;

		return callThiscall(ClientAddresses::Function::TreeNodeAttach, int, TreeNode*, TreeNode*)(this->TMHuman, element);
	}
 
	//----- (004B8A99) --------------------------------------------------------
	int ReloadScene(int a2 = 9)
	{
		return callThiscall(ClientAddresses::Function::TMSceneReload, int, TMScene*, int)(this, a2);
	}

	signed int ReadFile(const char* file)
	{
		return callThiscall(ClientAddresses::Function::TMSceneReadFile, signed int, TMScene*, const char*)(this, file);
	}

	int removeElement(SControl* _va)
	{
		if (_va)
			return callThiscall(ClientAddresses::Function::TreeNodeDispose, int, SControl*)(_va);

		return 0;
	}

	short  UpdateGrid(SGridControlItem* ControlItem, short a3 = 0, short a4 = 0)
	{
		return callThiscall(ClientAddresses::Function::TMSceneUpdateGrid, short, TMScene*, SGridControlItem*, short, short)(this, ControlItem, a3, a4);
	}


	int removeElementByHandle(int handle)
	{
		if (auto val = this->FindControl<SControl>(handle))
			return val->Dispose();
		return 0;
	}

	uint32_t  getTMScene()
	{//att
		static uint32_t rtnValue = 0;

		__asm
		{
			MOV EAX, DWORD PTR DS : [CLIENT_ADDR_TM_SCENE]
			MOV rtnValue, EAX
		}

		if (rtnValue == 0)
			return uint32_t();

		return  rtnValue;
	}


	void ShowBox(int Handle, const char* Message, int Row = 0, int Column = 0)
	{//att
		auto _This = this->getTMScene();
		if (!_This || !Message)
			return;

		auto messageBox = *(DWORD*)(_This + 204);
		if (!messageBox || !*(DWORD*)messageBox)
			return;

		// by FREEDOM
		(*(void(__thiscall**)(DWORD, void*, signed int, DWORD))(*(DWORD*)messageBox + 140))(messageBox, (char*)Message, Handle, 0);
		*(DWORD*)(messageBox + 488) = Column | (Row << 16);
		(*(void(__thiscall**)(DWORD, signed int))(*(DWORD*)messageBox + 96))(messageBox, 1);
	}
	int getHandleParse()
	{//att
		if (!this)
			return 0;

		auto messageBox = *(DWORD*)(reinterpret_cast<unsigned int>(this) + 204);
		return messageBox ? *(DWORD*)(messageBox + 492) : 0;
	}
	int getParmParse()
	{//att
		if (!this)
			return 0;

		auto messageBox = *(DWORD*)(reinterpret_cast<unsigned int>(this) + 204);
		return messageBox ? *(DWORD*)(messageBox + 488) : 0;
	}
	void ShowBoxParm(int Handle, const char* Message, int Parm)
	{//att
		auto _This = this->getTMScene();
		if (!_This || !Message)
			return;

		auto messageBox = *(DWORD*)(_This + 204);
		if (!messageBox || !*(DWORD*)messageBox)
			return;

		// by FREEDOM
		(*(void(__thiscall**)(DWORD, void*, signed int, DWORD))(*(DWORD*)messageBox + 140))(messageBox, (char*)Message, Handle, 0);
		*(DWORD*)(messageBox + 488) = Parm;
		(*(void(__thiscall**)(DWORD, signed int))(*(DWORD*)messageBox + 96))(messageBox, 1);
	}


	void NoExecute()
	{
		auto _This = this->getTMScene();
		if (!_This)
			return;

		auto clientMessage = *(DWORD*)(_This + 196);
		if (!clientMessage || !*(DWORD*)clientMessage)
			return;

		(*(void(__thiscall**)(DWORD, signed int, signed int))(*(DWORD*)clientMessage + 136))(clientMessage, 1, 1);
	}

	void inputFocus(SControl* controlBox)
	{
		auto v49 = this->getTMScene();
		if (!v49 || !controlBox)
			return;

		auto interfacePtr = *(DWORD*)(v49 + 40);
		if (!interfacePtr || !*(DWORD*)interfacePtr)
			return;

		(*(void(__thiscall**)(DWORD, SControl*))(*(DWORD*)interfacePtr + 64))(interfacePtr, controlBox);
	}

	void addLog(const char *Str)
	{
		ClientFunctions::setLog("%s", Str);
	}
	template <class T> T* FindControl(signed int handleId)
	{//att by seitbnao
		if (!this)
			return 0;

		auto _This = this->getTMScene();
		if (!_This)
			return 0;

		auto interfacePtr = *(DWORD*)(_This + 40);
		if (!interfacePtr || !*(DWORD*)interfacePtr)
			return 0;

		auto ret =  (*(T * (__thiscall**)(DWORD, signed int))(*(DWORD*)interfacePtr + 72))(interfacePtr, handleId);
		if (!ret)
		{
			this->addLog(_STR("(::%s)Ponteiro nulo ou inexistente id %d", __FUNCSIG__, handleId));
			return 0;
		}
		return ret;
	}

	template <class T> T* getGuiFromValue(signed int value)
	{//att by seitbnao		
		if (!this)
			return 0;

		auto ret = reinterpret_cast<T*>(*(DWORD*)(reinterpret_cast<DWORD>(this) + value));
		if (!ret)
		{
			this->addLog(_STR("(::%s)Ponteiro nulo ou inexistente value %d", __FUNCSIG__, value));
			return 0;
		}
		return ret;
	}
	template <class T> T* getGuiFromValue(signed int value, int i)
	{//att by seitbnao		
		if (!this)
			return 0;

		auto ret = reinterpret_cast<T*>(*(DWORD*)(reinterpret_cast<DWORD>(this) + (value + i * 4)));
		if (!ret)
		{
			this->addLog(_STR("(::%s)Ponteiro nulo ou inexistente value %d i %d", __FUNCSIG__, value,i));
			return 0;
		}
		return ret;
	}
	//  DeltaTime
	static int getDeltaTime() {
		int* DeltaTimeAddr = *(int**)ClientAddresses::Memory::DeltaTime;
		if (!DeltaTimeAddr || !*(DWORD*)DeltaTimeAddr)
			return 0;

		return (*(int(__thiscall**)(int*))(*(DWORD*)DeltaTimeAddr + 8))(DeltaTimeAddr);
	};

	void  OpeCargo(int a3 = 0)
	{//by seitbnao
		//att
		static int onexecute_addr = ClientAddresses::Function::TMSceneOpenCargo;
		__asm
		{
			MOV EAX, CLIENT_ADDR_TM_SCENE
			MOV EDX, DWORD PTR DS : [EAX]

			PUSH a3
			MOV ECX, EDX
			MOV EAX, onexecute_addr
			CALL EAX
		}
	}

	//Simula um click de algum handled, pode fechar janelas ou ate mesmo fazer um auto login
	void  onExecute(int Handled, int a3 = 0)
	{//by seitbnao
		//att
		static int onexecute_addr = ClientAddresses::Function::TMSceneOnExecute;
		__asm
		{
			MOV EAX, CLIENT_ADDR_TM_SCENE
			MOV EDX, DWORD PTR DS : [EAX]

			PUSH a3
			PUSH Handled
			MOV ECX, EDX
			MOV EAX, onexecute_addr
			CALL EAX
		}
	}


	SCursor* getCursor()
	{
		auto scene = getTMScene();
		return scene ? reinterpret_cast<SCursor*>((DWORD*)(scene + 12)) : nullptr;
	}
	SControl* getElementFromValue(int i, int value)
	{
		if (!this)
			return nullptr;

		return reinterpret_cast<SControl*>((reinterpret_cast<DWORD>(this) + value + 4 * i));
	}

	void CloseWindow(int Hande)
	{
		auto window = this->FindControl<SPanel>(Hande);
		if (window)
			window->SetVisibility(!window->Visibility);
	}

	SText* getLabelBuffs()
	{
		auto _This = this->getTMScene();
		return _This ? reinterpret_cast<SText*>((DWORD*)(_This + 541792)) : nullptr;
	}

	SListBox* getPartyList()
	{
		auto _This = this->getTMScene();
		return _This ? reinterpret_cast<SListBox*>((DWORD*)(_This + 541884)) : nullptr;
	}

	static TMScene* MouseItem()
	{
		// Instance
		PDWORD g_pGameClass = (PDWORD)ClientAddresses::Memory::TMMouseItem;
		// Return Instance
		return (TMScene*)(*g_pGameClass);
	}
	
	SGridControlItem *MouseControlItem()
	{
		return this->getGuiFromValue<SGridControlItem>(488);
	}
 
	void ClearMouseItem(SGridControlItem *Pointer)
	{
		if (!Pointer)
			return;

		PDWORD g_pGameClass = (PDWORD)ClientAddresses::Memory::TMMouseItem;

		if (*(DWORD*)(g_pGameClass + 488) && *(DWORD*)(g_pGameClass + 488) == *(DWORD*)(Pointer))
		{
			*(DWORD*)(g_pGameClass + 488) = 0;
		}
	}
	 
	template<class T> void insertComponente(T* Class)
	{
		auto _This = this->getTMScene();
		if (!_This || !Class)
			return;

		auto interfacePtr = *(DWORD*)(_This + 40);
		if (!interfacePtr || !*(DWORD*)interfacePtr)
			return;

		return (*(void(__thiscall**)(DWORD, T*))(*(DWORD*)interfacePtr + 68))(interfacePtr, Class);
	}

	template<class T> static void addElement(T* Class)
	{
		static uint32_t rtnValue = 0;

		__asm
		{
			MOV EAX, DWORD PTR DS : [CLIENT_ADDR_TM_SCENE]
			MOV rtnValue, EAX
		}

		if (!rtnValue || !Class)
			return;

		auto interfacePtr = *(DWORD*)(rtnValue + 40);
		if (!interfacePtr || !*(DWORD*)interfacePtr)
			return;

		return (*(void(__thiscall**)(DWORD, T*))(*(DWORD*)interfacePtr + 68))(interfacePtr, Class);
	}

	bool CheckVisibility(int handle, bool setvisible = false)
	{
		if (auto p = this->FindControl<SControl>(handle))
		{
			if (p->Visibility)
			{
				if (setvisible)
					p->Visibility = 0;

				return true;
			}
			return false;
		}

		return false;
	}
	int GetComponentsCount() {
		return *(int*)ClientAddresses::Memory::ComponentCount;
	}


	//----- (004A207A) --------------------------------------------------------
	int  sub_4A207A(float a2, float a3)
	{
		return callThiscall(ClientAddresses::Function::TMSceneProjectPosition, int, TMScene*, float, float)(this, a2, a3);
	}
 
	//HOOKS
 
	static int ControleDeTeclas(TMScene* main, char Key);
	static int ControlMessageBox(TMScene* Main, int ClientTick);
	static void SEditableTextMouseControl(SEditableText* Element, int MouseMode, int posX, int posY);
	

	void CTSceneLogin();

	void CTSceneSelChar();

	void CTSceneWorld();

	static void HKD_Inventory(UINT32 Open);

	static void LoadSceneControl(int Scene);

	static void SControlMouseController(SControl* Control, int mouseStatus, int posX, int posY, int mouseState);

	static void HKD_KeyScapeControl();

	static void STextMouseController(SControl* Control, int unk1, int mouseEvent, int posX, int posY);

};

#define pInfo(t,handle) (TMScene::Instance() ? TMScene::Instance()->FindControl<t>(handle) : nullptr)
#define InterPoint(t,handle) auto pointer = pInfo(t,handle)
