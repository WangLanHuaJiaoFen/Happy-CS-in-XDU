#include <linux/init.h>
#include <linux/module.h>
#include <linux/proc_fs.h>
#include <asm/uaccess.h>
#include <linux/sched.h>
#include <linux/kernel.h>
#include<linux/sched/signal.h>
MODULE_LICENSE("GPL");

static int num = -1;

module_param(num, int, S_IRUGO);

static __init int exp_init(void){
  struct task_struct *p = NULL;
  for_each_process(p)
  {
    if (num==0 )
      break;
    printk("pid=%d,path=%s\n", p->pid, p->comm);
    num--;
  }

  return 0;
}

static __exit void exp_exit(void){
  printk("Good bye.\n");
}

module_init(exp_init);
module_exit(exp_exit);


