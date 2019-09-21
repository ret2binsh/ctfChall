import angr
import logging

#logging.getLogger('angr').setLevel('ERROR')

def solve_depth2(state):
    # offsets for the backdoor function through the menu
    #find_addr2 = 0x401406
    find_addr = 0x40147a
    #avoid_addr2 = [0x401412,0x401423,0x4013f1]
    avoid_addr = [0x40159b,0x401586,0x401568,0x401571,0x401578,0x40157f]

    #state2 = project.factory.entry_state()
    # build manager2
    simgr2 = project.factory.simulation_manager(state)
    simgr2.use_technique(angr.exploration_techniques.Explorer())

    try:
        # attempt to solve depth 2 leveraging state from mgr1
        simgr2.explore(find=find_addr, avoid=avoid_addr)
        found = simgr2.found[0]
        result = found.posix.dumps(0).split(b'\n')
        depth1 = result[0].decode('utf-8')
        depth2 = result[1]
        print("Raw solve: %s" % found.posix.dumps(0))
        print("Solutions: \nDepth 1:%s \nDepth 2:%s" % (depth1,depth2))
    except:
        print("Failed to solve depth2.")

if __name__ == "__main__":

    binary = "bank"
    
    print("Loading new Project.")
    project = angr.Project(binary)
    #print("Beginning depth1 solve....")
    state = project.factory.entry_state()
    #state = solve_depth1(project)
    print("Beginning depth2 solve....")
    solve_depth2(state)
