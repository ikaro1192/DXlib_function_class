#ifndef GARD_CHECK_HITKEY_MOMENT_POLICY
#define GARD_CHECK_HITKEY_MOMENT_POLICY


namespace turara_soft{
namespace function{
class NoarmalWait{
public:
	bool check(){return false;}
	void clear(){}
private:
};

//������邩���X�e�b�v���܂Ō��o���Ȃ�
template<int Step>
class StepWait{
public:
    StepWait();
	
	bool check();//{return false;}
	void clear();
private:
	int StepCounter;
	enum{WaitStep=Step};
};
//�ŏ��̐��X�e�b�v�͌��o���A���̌㌟�o���Ȃ�
template<int Step>
class PretermitFewStepWait{
public:
    PretermitFewStepWait();
	
	bool check();
	void clear();
private:
	int StepCounter;
	enum{WaitStep=Step};
};

//������邩��莞��[ms]���܂Ō��o���Ȃ�
template<int Time>
class TimeWait{
public:
	bool check(){return false;}
	void clear(){}
private:
	enum{WaitStep=Time};
};
}
}
//�|���V�[����
//StepWait
template<int StepWait>
turara_soft::function::StepWait<StepWait>::StepWait():StepCounter(0){}

template<int StepWait>
bool turara_soft::function::StepWait<StepWait>::check(){
	if (StepCounter==StepWait){
		this->clear();
		return true;
	}
	StepCounter++;
	return false;
}

template<int StepWait>
void turara_soft::function::StepWait<StepWait>::clear(){StepCounter=0;}


//PretermitFewStepWait
template<int StepWait>
turara_soft::function::PretermitFewStepWait<StepWait>::PretermitFewStepWait():StepCounter(0){}

template<int StepWait>
bool turara_soft::function::PretermitFewStepWait<StepWait>::check(){
	StepCounter++;
	if (StepCounter<StepWait) return true;
	return false;
}

template<int StepWait>
void turara_soft::function::PretermitFewStepWait<StepWait>::clear(){StepCounter=0;}

#endif