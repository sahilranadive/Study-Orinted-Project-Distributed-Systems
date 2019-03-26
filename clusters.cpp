#include <bits/stdc++.h>
#include <iostream>

using namespace std;

typedef struct{
  int time;
  int data;
  int label;//0: data, 1: time,2:other
  float wait_time;
  float run_time;
  float end_time;
}job;

typedef struct{
  deque<job> q;
  long int data_storage;
  long int processing_power;
  vector<job> jobs_processed;
  float time;
}cluster;

int invector=0;

float abs(float a,float b){
  if(a<=b)
    return b-a;
  else
    return a-b;
}

int findMax(float a,float b, float c){
  if(abs(a,b)<100 && abs(b,c)<100 && abs(a,c)<100)
    return 0;
  if(a>=b&&a>=c)
    return 1;
  if(b>=a&&b>=c)
    return 2;
  if(c>=a&&c>=b)
    return 3;
}
int findMin(float a,float b, float c){
  if(a<=b&&a<=c)
    return 1;
  if(b<=a&&b<=c)
    return 2;
  if(c<=a&&c<=b)
    return 3;
}

cluster removeJob(cluster c){
  int pos = -1;
  float min_time = 1000000;
  int data_free = 0;
  for(int i = 0; i < c.jobs_processed.size();i++){
    if(c.jobs_processed[i].end_time<min_time){
      data_free = c.jobs_processed[i].data;
      min_time = c.jobs_processed[i].end_time;
      pos = i;
    }
  }
  c.jobs_processed.erase(c.jobs_processed.begin()+pos);
  c.data_storage = c.data_storage+data_free;
  c.time = min_time;
  return c;
}


int main(){
  FILE* fp = fopen("modified.csv","r");
  char buf[255];
  vector<job> jobs;
  fgets(buf,255,fp);

  while(fgets(buf,255,fp)){

    char* tok = strtok(buf,",");
    job j;
    int i = 0;
    //while(tok){
      //if(i==0){
        j.time = atoi(tok);
        tok = strtok(NULL,",");
      //}
      //else if(i==1){
        j.data = atoi(tok);
        tok = strtok(NULL,",");
      //}
      //else{
        j.label = atoi(tok);
      //}
      i++;
     // tok = strtok(NULL,",");
    //}
      jobs.push_back(j);
  }
  printf("all jobs created\n");

  //vector<cluster> clusters;
  cluster data;
  data.data_storage = 1000000;
  data.processing_power = 1000;
  //data.jobs_processed = 0;
  cluster t;
  t.data_storage = 10000000;
  t.processing_power = 1000;
  //t.jobs_processed = 0;
  cluster other;
  other.data_storage = 100000;
  other.processing_power = 1000;
  //other.jobs_processed = 0;

  // clusters.push_back(data);
  // clusters.push_back(t);
  // clusters.push_back(other);
int flag1 = 0;
int flag2 = 0;
int flag3 = 0;
  for(int i = 0; i < jobs.size(); i++){

    if(jobs[i].label==0){

      if(data.data_storage-jobs[i].data>=0){
        data.data_storage=data.data_storage-jobs[i].data;
        //data.jobs_processed++;
        jobs[i].wait_time = 0;
      //  cout<<flag1<<endl;
        if(flag1==1){
          jobs[i].wait_time = data.q.back().wait_time;
          //cout<<"wait time = "<<data.q.back().end_time<<endl;
        }
        jobs[i].run_time = jobs[i].data/data.processing_power;
        jobs[i].end_time = jobs[i].wait_time+jobs[i].run_time;
        data.jobs_processed.push_back(jobs[i]);
        invector++;
        //printf("cluster data vector%f %f %f\n",jobs[i].wait_time,jobs[i].run_time,jobs[i].end_time);
      }
      else{
      	//printf("did not enter directly\n");
        flag1 = 1;
        while(data.data_storage-jobs[i].data<0){
          data = removeJob(data);
          jobs[i].wait_time = data.time;

        }
        jobs[i].run_time = jobs[i].data/data.processing_power;
        jobs[i].end_time = jobs[i].wait_time+jobs[i].run_time;
        data.data_storage = data.data_storage-jobs[i].data;
        data.jobs_processed.push_back(jobs[i]);
        //printf("cluster data 2vector%f %f %f\n",jobs[i].wait_time,jobs[i].run_time,jobs[i].end_time);
      }

      data.q.push_back(jobs[i]);
      //cout<<data.q.back().end_time<<endl;
    }
    else if(jobs[i].label==1){
      if(t.data_storage-jobs[i].data>=0){
        t.data_storage=t.data_storage-jobs[i].data;
        //data.jobs_processed++;
        jobs[i].wait_time = 0;
        if(flag2==1){
          jobs[i].wait_time = t.q.back().wait_time;
          //cout<<"wait time = "<<data.q.back().end_time<<endl;
        }
        jobs[i].run_time = jobs[i].data/t.processing_power;
        jobs[i].end_time = jobs[i].wait_time+jobs[i].run_time;
        t.jobs_processed.push_back(jobs[i]);
        invector++;
        //printf("cluster time vector%f %f %f\n",jobs[i].wait_time,jobs[i].run_time,jobs[i].end_time);

      }
      else{
        flag2 = 1;
      	//printf("going2\n");
        while(t.data_storage-jobs[i].data<0){
          t = removeJob(t);
          jobs[i].wait_time = t.time;

        }



        jobs[i].run_time = jobs[i].data/t.processing_power;
        jobs[i].end_time = jobs[i].wait_time+jobs[i].run_time;
        t.data_storage = t.data_storage-jobs[i].data;
        t.jobs_processed.push_back(jobs[i]);
        //printf("cluster time 2vector%f %f %f\n",jobs[i].wait_time,jobs[i].run_time,jobs[i].end_time);
      }
      t.q.push_back(jobs[i]);
    }
    else{
      if(other.data_storage-jobs[i].data>=0){
        other.data_storage=other.data_storage - jobs[i].data;
        //data.jobs_processed++;
        jobs[i].wait_time = 0;
        if(flag3==1){
          jobs[i].wait_time = other.q.back().wait_time;
          //cout<<"wait time = "<<data.q.back().end_time<<endl;
        }
        jobs[i].run_time = jobs[i].data/other.processing_power;
        jobs[i].end_time = jobs[i].wait_time+jobs[i].run_time;
        other.jobs_processed.push_back(jobs[i]);
        invector++;
        //printf("cluster other vector%f %f %f\n",jobs[i].wait_time,jobs[i].run_time,jobs[i].end_time);

      }
      else{
      	//printf("going3\n");
        flag3 = 1;
        while(other.data_storage-jobs[i].data<0){
          other = removeJob(other);
          jobs[i].wait_time = other.time;
          //other.jobs_processed.push_back(jobs[i]);
        }

        jobs[i].run_time = jobs[i].data/other.processing_power;
        jobs[i].end_time = jobs[i].wait_time+jobs[i].run_time;
        other.data_storage = other.data_storage-jobs[i].data;
        other.jobs_processed.push_back(jobs[i]);
        //printf("cluster other 2vector%f %f %f\n",jobs[i].wait_time,jobs[i].run_time,jobs[i].end_time);
      }
      other.q.push_back(jobs[i]);
    }
  }
  cout<<"print time before migration:"<<endl;
  cout<<data.q.back().end_time<<endl;
  cout<<t.q.back().end_time<<endl;
  cout<<other.q.back().end_time<<endl;
  while(1){
    int max = findMax(data.q.back().wait_time,t.q.back().wait_time,other.q.back().wait_time);
    int min = findMin(data.q.back().wait_time,t.q.back().wait_time,other.q.back().wait_time);
    if(max == 0)
      break;
    if(max==1 && min==2){
      job j = data.q.back();
      data.q.pop_back();
      if(t.data_storage-j.data>=0){
        t.data_storage=t.data_storage-j.data;
        //data.jobs_processed++;
        j.wait_time = t.q.back().wait_time;
          //cout<<"wait time = "<<data.q.back().end_time<<endl;
        j.run_time = j.data/t.processing_power;
        j.end_time = j.wait_time+j.run_time;
        t.jobs_processed.push_back(j);
        //invector++;
        //printf("cluster time vector%f %f %f\n",jobs[i].wait_time,jobs[i].run_time,jobs[i].end_time);

      }
      else{
        //flag2 = 1;
      	//printf("going2\n");
        while(t.data_storage-j.data<0){
          t = removeJob(t);
          j.wait_time = t.time;

        }



        j.run_time = j.data/t.processing_power;
        j.end_time = j.wait_time+j.run_time;
        t.data_storage = t.data_storage-j.data;
        t.jobs_processed.push_back(j);
        //printf("cluster time 2vector%f %f %f\n",jobs[i].wait_time,jobs[i].run_time,jobs[i].end_time);
      }
      t.q.push_back(j);
    }
    if(max==1 && min==3){
      job j = data.q.back();
      data.q.pop_back();
      if(other.data_storage-j.data>=0){
        other.data_storage=t.data_storage-j.data;
        //data.jobs_processed++;
        j.wait_time = other.q.back().wait_time;
          //cout<<"wait time = "<<data.q.back().end_time<<endl;
        j.run_time = j.data/other.processing_power;
        j.end_time = j.wait_time+j.run_time;
        other.jobs_processed.push_back(j);
        //invector++;
        //printf("cluster time vector%f %f %f\n",jobs[i].wait_time,jobs[i].run_time,jobs[i].end_time);

      }
      else{
        //flag2 = 1;
        //printf("going2\n");
        while(other.data_storage-j.data<0){
          other = removeJob(other);
          j.wait_time = other.time;

        }



        j.run_time = j.data/other.processing_power;
        j.end_time = j.wait_time+j.run_time;
        other.data_storage = other.data_storage-j.data;
        other.jobs_processed.push_back(j);
        //printf("cluster time 2vector%f %f %f\n",jobs[i].wait_time,jobs[i].run_time,jobs[i].end_time);
      }
      other.q.push_back(j);
    }
    if(max==2 && min==3){
      job j = t.q.back();
      t.q.pop_back();
      if(other.data_storage-j.data>=0){
        other.data_storage=t.data_storage-j.data;
        //data.jobs_processed++;
        j.wait_time = other.q.back().wait_time;
          //cout<<"wait time = "<<data.q.back().end_time<<endl;
        j.run_time = j.data/other.processing_power;
        j.end_time = j.wait_time+j.run_time;
        other.jobs_processed.push_back(j);
        //invector++;
        //printf("cluster time vector%f %f %f\n",jobs[i].wait_time,jobs[i].run_time,jobs[i].end_time);

      }
      else{
        //flag2 = 1;
        //printf("going2\n");
        while(other.data_storage-j.data<0){
          other = removeJob(other);
          j.wait_time = other.time;

        }



        j.run_time = j.data/other.processing_power;
        j.end_time = j.wait_time+j.run_time;
        other.data_storage = other.data_storage-j.data;
        other.jobs_processed.push_back(j);
        //printf("cluster time 2vector%f %f %f\n",jobs[i].wait_time,jobs[i].run_time,jobs[i].end_time);
      }
      other.q.push_back(j);
    }
    if(max==2 && min==1){
      job j = t.q.back();
      t.q.pop_back();
      if(data.data_storage-j.data>=0){
        data.data_storage=t.data_storage-j.data;
        //data.jobs_processed++;
        j.wait_time = data.q.back().wait_time;
          //cout<<"wait time = "<<data.q.back().end_time<<endl;
        j.run_time = j.data/data.processing_power;
        j.end_time = j.wait_time+j.run_time;
        data.jobs_processed.push_back(j);
        //invector++;
        //printf("cluster time vector%f %f %f\n",jobs[i].wait_time,jobs[i].run_time,jobs[i].end_time);

      }
      else{
        //flag2 = 1;
        //printf("going2\n");
        while(data.data_storage-j.data<0){
          data = removeJob(data);
          j.wait_time = data.time;

        }



        j.run_time = j.data/data.processing_power;
        j.end_time = j.wait_time+j.run_time;
        data.data_storage = data.data_storage-j.data;
        data.jobs_processed.push_back(j);
        //printf("cluster time 2vector%f %f %f\n",jobs[i].wait_time,jobs[i].run_time,jobs[i].end_time);
      }
      data.q.push_back(j);
    }
    if(max==3 && min==1){
      job j = other.q.back();
      other.q.pop_back();
      if(data.data_storage-j.data>=0){
        data.data_storage=t.data_storage-j.data;
        //data.jobs_processed++;
        j.wait_time = data.q.back().wait_time;
          //cout<<"wait time = "<<data.q.back().end_time<<endl;
        j.run_time = j.data/data.processing_power;
        j.end_time = j.wait_time+j.run_time;
        data.jobs_processed.push_back(j);
        //invector++;
        //printf("cluster time vector%f %f %f\n",jobs[i].wait_time,jobs[i].run_time,jobs[i].end_time);

      }
      else{
        //flag2 = 1;
        //printf("going2\n");
        while(data.data_storage-j.data<0){
          data = removeJob(data);
          j.wait_time = data.time;

        }



        j.run_time = j.data/data.processing_power;
        j.end_time = j.wait_time+j.run_time;
        data.data_storage = data.data_storage-j.data;
        data.jobs_processed.push_back(j);
        //printf("cluster time 2vector%f %f %f\n",jobs[i].wait_time,jobs[i].run_time,jobs[i].end_time);
      }
      data.q.push_back(j);
    }
    if(max==3 && min==2){
      job j = other.q.back();
      other.q.pop_back();
      if(t.data_storage-j.data>=0){
        t.data_storage=t.data_storage-j.data;
        //data.jobs_processed++;
        j.wait_time = t.q.back().wait_time;
          //cout<<"wait time = "<<data.q.back().end_time<<endl;
        j.run_time = j.data/t.processing_power;
        j.end_time = j.wait_time+j.run_time;
        t.jobs_processed.push_back(j);
        //invector++;
        //printf("cluster time vector%f %f %f\n",jobs[i].wait_time,jobs[i].run_time,jobs[i].end_time);

      }
      else{
        //flag2 = 1;
      	//printf("going2\n");
        while(t.data_storage-j.data<0){
          t = removeJob(t);
          j.wait_time = t.time;

        }



        j.run_time = j.data/t.processing_power;
        j.end_time = j.wait_time+j.run_time;
        t.data_storage = t.data_storage-j.data;
        t.jobs_processed.push_back(j);
        //printf("cluster time 2vector%f %f %f\n",jobs[i].wait_time,jobs[i].run_time,jobs[i].end_time);
      }
      t.q.push_back(j);
    }
  }
  cout<<"print time after migration:"<<endl;
  cout<<data.q.back().end_time<<endl;
  cout<<t.q.back().end_time<<endl;
  cout<<other.q.back().end_time<<endl;
  // cout<<invector<<endl;
  // for(int i = 0; i< jobs.size();i++){
  //   cout<<jobs[i].end_time<<endl;
  // }
}
