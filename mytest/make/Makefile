
all: 1.l1 2.l1 3.l1
	@$(call time_stt, $@, echo build all 1; sleep 1)
	@$(call time_stt, $@, echo build all 2; sleep 1)
	@$(call time_stt, $@, echo build all 3; sleep 1)
	@$(call time_stt, $@, echo build all 4; sleep 1)
	@$(call time_stt, $@, echo build all 5; sleep 1)
	touch $@
	

1.l1: 1.l2 2.l2 3.l2
	@$(call time_stt, $@, echo build $@ from $^ 1; sleep 3)
	@$(call time_stt, $@, echo build $@ from $^ 2; sleep 3)
	@$(call time_stt, $@, echo build $@ from $^ 3; sleep 3)
	touch $@

2.l1: 4.l2 5.l2 6.l2 $(DUMMY1) $(DUMMY2) $(DUMMY3)
	@$(call time_stt, $@, echo build $@ from $^ 1; sleep 2)
	@$(call time_stt, $@, echo build $@ from $^ 2; sleep 2)
	@$(call time_stt, $@, echo build $@ from $^ 3; sleep 2)
	touch $@

#@echo dd $@ d1 $(DUMMY1) d2 $(DUMMY2) D3 $(DUMMY3)

3.l1: dum dum2 $(DUMMY3) 7.l2
	@$(call time_stt, $@, echo build $@ from $^ 1; sleep 1)
	@$(call time_stt, $@, echo build $@ from $^ 2; sleep 1)
	@$(call time_stt, $@, echo build $@ from $^ 3; sleep 1)
	@$(call time_stt, $@, echo build $@ from $^ 4; sleep 1)
	@$(call time_stt, $@, echo build $@ from $^ 5; sleep 1)
	@$(call time_stt, $@, echo build $@ from $^ 6; sleep 1)
	touch $@
	@$(call time_stt, $@, echo aaa $(DUMMY3) ; sleep 1)

%.l2:
	@$(call time_stt, $@, echo creating $@ 1; sleep 1)
	@$(call time_stt, $@, echo creating $@ 2; sleep 1)
	@$(call time_stt, $@, echo creating $@ 3; sleep 1)
	touch $@
	echo l2d $(DUMMY3)

dum2:
	@$(call time_stt, $@, echo bbb $(DUMMY3); sleep 1)

$(DUMMY3): mk_dir 51.l2
dum: mk_dir
	@$(call time_stt, $@, echo creating $@ ; sleep 1)

mk_dir:
	@$(call time_stt, $@, sleep 5;mkdir -p unity; touch unity/dummyfile.l3; echo create unityfiles; sleep 1)

DUMMY1=$(shell find . -name "*.l1")
DUMMY2=$(shell find . -name "*.l2")
DUMMY3=$(shell find unity -name "*.l3")



dddd: dddd1 dddd2

dddd1:33.l2 44.l2 .WAIT 55.l2

dddd2: 2.l1


#@echo dd $@ d1 $(DUMMY1) d2 $(DUMMY2) D3 $(DUMMY3)
	
define time_stt
	startts=`date +%s`;echo ssss pid=$$$$ $1;\
	$2;\
	endts=`date +%s`; echo uuuu $1 pid=$$$$ $$startts + $$((endts - startts)) = $$endts $(shell basename `pwd`)
endef

clean:
	rm -rf *.l1
	rm -rf *.l2
	rm -rf all
	rm -rf unity
	rm -rf *.fk


dummy:
	echo 1
	echo 2
	echo 3
	echo 4
	echo 5
	echo 6

task: task2

task: task1


task1:
	echo task1

task2:
	echo task2

fakeobj=fakeobj.ooo

PROCESS1=10
NUMBERS1 := $(shell seq 1 $(PROCESS1))
FILES1 := $(patsubst %,%.fk,$(NUMBERS1))

PROCESS2=20
NUMBERS2 := $(shell seq 11 $(PROCESS2))
FILES2 := $(patsubst %,%.fk,$(NUMBERS2))

realtasks1: $(FILES1)
realtasks2: $(FILES2)

%.fk: 
	@$(call time_stt, $@, touch $@;echo touch$@; sleep 1)
%.fk:
	@$(call time_stt, $@, touch $@;echo another touch$@; sleep 1)


prepare_flag=unity/ready_flag

test: $(prepare_flag) realtasks2

$(prepare_flag): generate_flag placehold
	
generate_flag: 
	@$(call time_stt, $@, mkdir -p unity; touch $(prepare_flag); sleep 3)

placehold: realtasks1 generate_flag
	
#.NOTPARALLEL:fakeobj 鸟东西没用，全局都串行

AOBJS=ab.xl a2.xl

TAROBJS=$(wildcard *.tar)
BOBJS=$(TAROBJS:.tar=.xl) b2.xl

$(AOBJS): aobjsreq
	@echo aojbs recipe
$(BOBJS): bobjsreq
	@echo bobjs recipe

aobjsreq:
	@echo this is aobjsreq

bobjsreq:
	@echo this is bobjsreq

