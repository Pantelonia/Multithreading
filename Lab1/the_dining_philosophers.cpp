class DiningPhilosophers {
private:
    bool forks[5];
    mutex m;
    mutex philosofer[5];
public:
    DiningPhilosophers() {
        for(int i=0;i<5;++i){
            forks[i]=true;
        }
    }
    
    bool check(int index1, int index2){
        
        m.lock();
        bool checked = forks[index1]&&forks[index2];
        if(checked){
            forks[index1] = false;
            forks[index2] = false;
        }
        m.unlock();
        return checked;
    }

    void wantsToEat(int philosopher,
                    function<void()> pickLeftFork,
                    function<void()> pickRightFork,
                    function<void()> eat,
                    function<void()> putLeftFork,
                    function<void()> putRightFork) {
      // Indexing at array start with zero. So first folk have index 0 and etc.  
        cout << philosopher << "\n" ;

        int left_fork_index = philosopher;
        int right_fork_index = philosopher+1;
        if(right_fork_index == 5)
            right_fork_index = 0;
        cout << left_fork_index << right_fork_index << "\n" ;        
        bool checked = check(left_fork_index,right_fork_index);
        //This loop wait the momemt when folk will be free
        while(!checked){
            philosofer[philosopher].lock();
            checked=check(left_fork_index,right_fork_index);
        }
        
        pickLeftFork();
        pickRightFork();
        eat();
        putLeftFork();
        putRightFork();
        
        forks[left_fork_index] = true;
        forks[right_fork_index] = true;
        
        int pre=philosopher-1;
        if(pre==-1){
            pre=4;
        }
        
        philosofer[pre].unlock();
        philosofer[philosopher].unlock();
        philosofer[right_fork_index].unlock();
        
    }
};