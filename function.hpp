#include "DxLib.h"
#include<string>
#include<map>
#include "check_hitKey_moment_policy.hpp"

#ifndef GARD_FUNCTION
#define GARD_FUNCTION

namespace turara_soft{
namespace function{
template<typename> class CheckHitKeyMoment;
class NoarmalWait;//CheckHitKeyMoment�̃|���V�[

//====================================limit====================================
//�l�͈̔͂𐧌�����ׂ̊֐�
//�ۂ߂��l=limit(�ۂ߂�l,����,���)
template<typename T>
const T& limit(const T& input,const T& lower,const T& uper);


//===========================CheckHitKeyMoment Method===========================
//CheckHitKey���������u�Ԃ݂̂̔���ɂ���N���X(�t�@���N�^)
//�� �悭�l������KeyID�Ŏw�肷��ƕύX������...
//KeyID��DxLib��CheckHitKey�̒萔���Q��
//WaitPolicy�̓J�X�^�}�C�Y����ꍇ�̃|���V�[�N���X(���܂ł̊Ԋu�����߂铙)
//	WaitPolicy�̎��
//		NoarmalWait:��K�����ꂽ��͂Ȃ����܂Ō��o���Ȃ�
//		StepWait<int Step>:������邩���X�e�b�v���܂Ō��o���Ȃ�
//		PretermitFewStepWait<int Step>:�ŏ��̐��X�e�b�v�͌��o���A���̌㌟�o���Ȃ�
//		TimeWait<int Time>:������
template<typename WaitPolicy=NoarmalWait>
class CheckHitKeyMoment{
public:
	CheckHitKeyMoment(const int KeyID_);
	const bool operator()();
private:
	int KeyCounter;
	int KeyID;
	WaitPolicy WaitType;
};


//===============================ContentSelector===============================

//�_�C�A���O�Ȃǂ̑I�����������₷�����邽�߂̃N���X
template<int LineNum,int ColumnNum=1,class SelectTypePolicy=void>
class ContentSelector{
	public:
		ContentSelector();
		int getSelectedID()const{return SelectedID;}
		void checkKey();
	private:
		CheckHitKeyMoment<> UpKeyCheck; 
		CheckHitKeyMoment<> DownKeyCheck; 
		CheckHitKeyMoment<> LeftKeyCheck; 
		CheckHitKeyMoment<> RightKeyCheck;

		int SelectedID;//�I������Ă��鍀��

};


}//function�̏I���
}//icicle�̏I���


//=================================���\�b�h��`================================



//====================================limit====================================
template<typename T>
const T& turara_soft::function::limit(const T& input,const T& lower,const T& uper){
	if (input<lower)
		return lower;
	if (input>uper)
		return uper;
	return input;
}



//==============================CheckHitKeyMoment==============================
//�R���X�g���N�^
template<typename WaitPolicy>
turara_soft::function::CheckHitKeyMoment<WaitPolicy>::CheckHitKeyMoment(const int KeyID_):
	KeyID(KeyID_)
	{
	KeyCounter=0;
}

//�t�@���N�^�Ƃ��Ă��������߂�()�̃I�[�o�[���[�h
template<typename WaitPolicy>
const bool turara_soft::function::CheckHitKeyMoment<WaitPolicy>::operator ()(){
	if( CheckHitKey( KeyID ) == 1 ){
		if (KeyCounter==0){
			KeyCounter++;
			return true;
		}
		if (WaitType.check())return true;
	}else{
		if (KeyCounter>0){
			KeyCounter=0;
			WaitType.clear();
		}
	}
	return false;
}

//===============================ContentSelector===============================

template<int LineNum,int ColumnNum,class SelectTypePolicy>
turara_soft::function::ContentSelector<LineNum,ColumnNum,SelectTypePolicy>::ContentSelector():
	SelectedID(0),
	UpKeyCheck(KEY_INPUT_UP),
	DownKeyCheck(KEY_INPUT_DOWN),
	LeftKeyCheck(KEY_INPUT_LEFT),
	RightKeyCheck(KEY_INPUT_RIGHT)
	{
	
	
	}

template<int LineNum,int ColumnNum,class SelectTypePolicy>
void turara_soft::function::ContentSelector<LineNum,ColumnNum,SelectTypePolicy>::checkKey(){
	if ( UpKeyCheck() ){
		SelectedID-=ColumnNum;
	}
	if ( DownKeyCheck() ){
		SelectedID+=ColumnNum;
	}
	if (ColumnNum!=0){
		if ( RightKeyCheck() ){
			SelectedID++;
		}
		if ( LeftKeyCheck() ){
			SelectedID--;
		}
	}
	SelectedID=(SelectedID%(LineNum*ColumnNum)+LineNum*ColumnNum)%(LineNum*ColumnNum);//�֐����ł������B

}


#endif
