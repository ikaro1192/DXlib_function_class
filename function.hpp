#include "DxLib.h"
#include<string>
#include<map>
#include "check_hitKey_moment_policy.hpp"

#ifndef GARD_FUNCTION
#define GARD_FUNCTION

namespace turara_soft{
namespace function{
template<typename> class CheckHitKeyMoment;
class NoarmalWait;//CheckHitKeyMomentのポリシー

//====================================limit====================================
//値の範囲を制限する為の関数
//丸めた値=limit(丸める値,下限,上限)
template<typename T>
const T& limit(const T& input,const T& lower,const T& uper);


//===========================CheckHitKeyMoment Method===========================
//CheckHitKeyを押した瞬間のみの判定にするクラス(ファンクタ)
//※ よく考えたらKeyIDで指定すると変更が困難...
//KeyIDはDxLibのCheckHitKeyの定数を参照
//WaitPolicyはカスタマイズする場合のポリシークラス(次までの間隔を決める等)
//	WaitPolicyの種類
//		NoarmalWait:一階押されたらはなされるまで検出しない
//		StepWait<int Step>:離されるか一定ステップたつまで検出しない
//		PretermitFewStepWait<int Step>:最初の数ステップは検出し、その後検出しない
//		TimeWait<int Time>:未実装
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

//ダイアログなどの選択肢を扱いやすくするためのクラス
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

		int SelectedID;//選択されている項目

};


}//functionの終わり
}//icicleの終わり


//=================================メソッド定義================================



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
//コンストラクタ
template<typename WaitPolicy>
turara_soft::function::CheckHitKeyMoment<WaitPolicy>::CheckHitKeyMoment(const int KeyID_):
	KeyID(KeyID_)
	{
	KeyCounter=0;
}

//ファンクタとしてあつかうための()のオーバーロード
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
	SelectedID=(SelectedID%(LineNum*ColumnNum)+LineNum*ColumnNum)%(LineNum*ColumnNum);//関数化できそう。

}


#endif
