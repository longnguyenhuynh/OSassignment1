#include <linux/kernel.h>
//#include <unistd.h>
#include <linux/syscalls.h>

struct proc_info {
	pid_t pid;
	char name[16];
};

struct procinfos {
	long studentID;
	struct proc_info proc;
	struct proc_info parent_proc;
	struct proc_info oldest_child_proc;
};

SYSCALL_DEFINE2 (get_proc_info, pid_t, pid, struct procinfos*, info) {
	printk(KERN_INFO "Student ID: 1810700\n");
	info->studentID = 1810700;
	if (pid == -1) {
		pid = current->pid;
	}
	struct task_struct *process;
	for_each_process(process) {
		if (process->pid == pid) {
			info->proc.pid = process->pid;
			strcpy(info->proc.name, process->comm);
			if (process->real_parent == NULL) {
				info->parent_proc.pid = 0;
				strcpy(info->parent_proc.name, "\0");
			}	
			else {
				info->parent_proc.pid = process->real_parent->pid;
				strcpy(info->parent_proc.name, process->real_parent->comm);
			}
			struct task_struct * cProc;
			cProc = list_first_entry_or_null(&process->children, struct task_struct, sibling);
			if (cProc == NULL) {
				info->oldest_child_proc.pid = 0;
				strcpy(info->oldest_child_proc.name, "\0");
			}
			else {
				info->oldest_child_proc.pid = cProc->pid;
				strcpy(info->oldest_child_proc.name, cProc->comm);
			}	
		}
	}
	return 0;
}
