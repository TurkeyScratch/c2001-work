"""
:author:     James Jefferson Luu
:id:         30632749
:assignment: FIT1045 Assignment 2, Task 1 (Semester 1 2019)
:purpose:    Solves a best team solution using multiple techniques.
:created:    2019-11-14 (remade within 2 hours)
"""


def cost(candidates):
    return sum([person[1] for person in candidates])


def skills(candidates):
    skills_list = []
    for person in candidates:
        skills_list.extend(person[0])
    return list(dict.fromkeys(skills_list))


def uncovered(project, skills):
    project_set = set(project)
    return sorted(project_set.difference(skills), key=project.index)


def best_individual_candidate(project, candidates):
    ratio_candidates = [skill_cost(project, *person) for person in candidates]
    return ratio_candidates.index(max(ratio_candidates))


def skill_cost(project, skills, cost):
    skill_set = set(skills).intersection(project)
    return len(skill_set) / cost


def team_of_best_individuals(project, candidates):
    return _team_of_best_individuals(project[:], candidates[:])


def _team_of_best_individuals(project, candidates):
    if not (project and candidates):
        return []
    else:
        person = candidates.pop(best_individual_candidate(project, candidates))
        project = uncovered(project, person[0])
        return [person] + _team_of_best_individuals(project, candidates)


def next_bitlist(bitlist):
    current_bitlist, i = bitlist[:], len(bitlist) - 1
    while current_bitlist[i] == 1:
        current_bitlist[i] = 0
        i -= 1
    current_bitlist[i] = 1
    return current_bitlist


def bitlist_valid(bitlist, project, candidates):
    team_list = [person for i, person in enumerate(candidates) if bitlist[i]]
    return None if uncovered(project, skills(team_list)) else team_list


def team_bitlist(project, candidates):
    valid_teams, last_team = [len(candidates) * [0]], len(candidates) * [1]
    while valid_teams[-1] != last_team:
        valid_teams += [next_bitlist(valid_teams[-1])]
    return [bitlist_valid(b, project, candidates) for b in valid_teams]


def best_team(project, candidates):
    valid_teams = [t for t in team_bitlist(project, candidates) if t]
    teams_costs = [cost(team) for team in valid_teams]
    best_cost = teams_costs.index(min(teams_costs))
    return valid_teams[best_cost]
    
    
if __name__=="__main__":
    jess = (["php", "java"], 200)
    clark = (["php", "c++", "go"], 1000)
    john = (["lua"], 500)
    cindy = (["php", "go", "word"], 240)
    
    candidates = [jess, clark, john, cindy]
    project = ["php", "java", "c++", "lua", "go"]
    
    assert cost([john, cindy]) == 740
    assert skills([clark, cindy]) == ["php", "c++", "go", "word"]
    assert uncovered(project, skills([clark])) == ["java", "lua"]
    assert best_individual_candidate(project, candidates) == 0
    assert team_of_best_individuals(project, candidates) == \
        [jess, cindy, john, clark]
    assert best_team(project, candidates) == [jess, clark, john]
    
    print("No errors. All assert test cases were successful.\n")