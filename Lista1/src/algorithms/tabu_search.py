import random
from gtfs.graph_builder import GraphEdge
from algorithms.dijkstra import dijkstra
from algorithms.astar import astar_transfer


def calculate_route_cost_time(graph: dict[str, list[GraphEdge]], route: list[str], start_time: int) -> tuple[int, int]:
    total_time = start_time
    total_transfers = 0
    
    for i in range(len(route) - 1):
        _, arrival_time, transfers = dijkstra(graph, route[i], route[i+1], total_time)
        if arrival_time == float('inf'):
            return float('inf'), float('inf')
        total_time = arrival_time
        total_transfers += transfers
    
    return total_time - start_time, total_transfers


def calculate_route_cost_transfers(graph: dict[str, list[GraphEdge]], route: list[str], start_time: int) -> tuple[int, int]:
    total_time = start_time
    total_transfers = 0
    
    for i in range(len(route) - 1):
        if route[i] == route[i + 1]:
            arrival_time, transfers = total_time, 0
        else:
            path, arrival_time, transfers = astar_transfer(graph, route[i], route[i + 1], total_time)
            if not path:
                return float('inf'), float('inf')
        if arrival_time == float('inf'):
            return float('inf'), float('inf')
        total_time = arrival_time
        total_transfers += transfers
    
    return total_transfers, total_time - start_time


def get_2opt_neighbors(route: list[str], sample_size: int = None) -> list[tuple[list[str], tuple]]:
    neighbors = []
    n = len(route)
    
    for i in range(1, n - 1):
        for j in range(i + 1, n - 1):
            new_route = route[:i] + route[i:j+1][::-1] + route[j+1:]
            move = (i, j)
            neighbors.append((new_route, move))
    
    if sample_size and len(neighbors) > sample_size:
        neighbors = random.sample(neighbors, sample_size)
    
    return neighbors


"""Time minimization variants"""
# a
def tabu_search_time_basic(graph: dict[str, list[GraphEdge]], start: str, targets: list[str], start_time: int,max_iterations: int = 100) -> tuple[list[str], int, int]:
    route = [start] + targets + [start]
    s_best = route[:]
    
    tabu_list = []  
    iteration = 0
    
    while iteration < max_iterations:
        neighbors = get_2opt_neighbors(route)
        best_neighbor = None
        best_neighbor_cost = float('inf')
        best_neighbor_move = None
        
        for neighbor_route, move in neighbors:
            if move not in tabu_list:
                cost_time, _ = calculate_route_cost_time(graph, neighbor_route, start_time)
                if cost_time < best_neighbor_cost:
                    best_neighbor = neighbor_route
                    best_neighbor_cost = cost_time
                    best_neighbor_move = move
        
        if best_neighbor is None:
            break
        
        route = best_neighbor
        cost_time, transfers = calculate_route_cost_time(graph, route, start_time)
        
        best_cost, best_transfers = calculate_route_cost_time(graph, s_best, start_time)
        if cost_time < best_cost:
            s_best = route[:]
        
        if best_neighbor_move:
            tabu_list.append(best_neighbor_move)
        
        iteration += 1
    
    best_time, best_transfers = calculate_route_cost_time(graph, s_best, start_time)
    return s_best, best_time, best_transfers

#b
def tabu_search_time_variable_t(graph: dict[str, list[GraphEdge]], start: str, targets: list[str], start_time: int, max_iterations: int = 10000) -> tuple[list[str], int, int]:
    route = [start] + targets + [start]
    s_best = route[:]
    
    tabu_size = max(3, len(targets) // 2 + 1)  
    tabu_list = []  
    iteration = 0
    
    while iteration < max_iterations:
        neighbors = get_2opt_neighbors(route)
        best_neighbor = None
        best_neighbor_cost = float('inf')
        best_neighbor_move = None
        
        for neighbor_route, move in neighbors:
            if move not in tabu_list:
                cost_time, _ = calculate_route_cost_time(graph, neighbor_route, start_time)
                if cost_time < best_neighbor_cost:
                    best_neighbor = neighbor_route
                    best_neighbor_cost = cost_time
                    best_neighbor_move = move
        
        if best_neighbor is None:
            break
        
        route = best_neighbor
        cost_time, transfers = calculate_route_cost_time(graph, route, start_time)
        
        best_cost, best_transfers = calculate_route_cost_time(graph, s_best, start_time)
        if cost_time < best_cost:
            s_best = route[:]
        
        if best_neighbor_move:
            tabu_list.append(best_neighbor_move)
            if len(tabu_list) > tabu_size:
                tabu_list.pop(0)
        
        iteration += 1
    
    best_time, best_transfers = calculate_route_cost_time(graph, s_best, start_time)
    return s_best, best_time, best_transfers

#c
def tabu_search_time_aspiration(graph: dict[str, list[GraphEdge]], start: str, targets: list[str], start_time: int, max_iterations: int = 100) -> tuple[list[str], int, int]:
    route = [start] + targets + [start]
    s_best = route[:]
    best_cost, _ = calculate_route_cost_time(graph, s_best, start_time)
    
    tabu_size = max(3, len(targets) // 2 + 1)
    tabu_list = []
    iteration = 0
    
    while iteration < max_iterations:
        neighbors = get_2opt_neighbors(route)
        best_neighbor = None
        best_neighbor_cost = float('inf')
        best_neighbor_move = None
        
        for neighbor_route, move in neighbors:
            cost_time, _ = calculate_route_cost_time(graph, neighbor_route, start_time)
            
            aspiration_threshold = best_cost * 0.95
            
            if move not in tabu_list or cost_time < aspiration_threshold:
                if cost_time < best_neighbor_cost:
                    best_neighbor = neighbor_route
                    best_neighbor_cost = cost_time
                    best_neighbor_move = move
        
        if best_neighbor is None:
            break
        
        route = best_neighbor
        cost_time, transfers = calculate_route_cost_time(graph, route, start_time)
        
        if cost_time < best_cost:
            s_best = route[:]
            best_cost = cost_time
        
        if best_neighbor_move:
            tabu_list.append(best_neighbor_move)
            if len(tabu_list) > tabu_size:
                tabu_list.pop(0)
        
        iteration += 1
    
    best_time, best_transfers = calculate_route_cost_time(graph, s_best, start_time)
    return s_best, best_time, best_transfers

#d
def tabu_search_time_sampling(graph: dict[str, list[GraphEdge]], start: str, targets: list[str], start_time: int, max_iterations: int = 100) -> tuple[list[str], int, int]:
    route = [start] + targets + [start]
    s_best = route[:]
    
    tabu_size = max(3, len(targets) // 2 + 1)
    tabu_list = []
    iteration = 0
    
    max_sample_size = min(20, max(5, int((len(targets) ** 1.5) / 2)))
    
    while iteration < max_iterations:
        neighbors = get_2opt_neighbors(route, sample_size=max_sample_size)
        best_neighbor = None
        best_neighbor_cost = float('inf')
        best_neighbor_move = None
        
        for neighbor_route, move in neighbors:
            if move not in tabu_list:
                cost_time, _ = calculate_route_cost_time(graph, neighbor_route, start_time)
                if cost_time < best_neighbor_cost:
                    best_neighbor = neighbor_route
                    best_neighbor_cost = cost_time
                    best_neighbor_move = move
        
        if best_neighbor is None:
            break
        
        route = best_neighbor
        cost_time, transfers = calculate_route_cost_time(graph, route, start_time)
        
        best_cost, best_transfers = calculate_route_cost_time(graph, s_best, start_time)
        if cost_time < best_cost:
            s_best = route[:]
        
        if best_neighbor_move:
            tabu_list.append(best_neighbor_move)
            if len(tabu_list) > tabu_size:
                tabu_list.pop(0)
        
        iteration += 1
    
    best_time, best_transfers = calculate_route_cost_time(graph, s_best, start_time)
    return s_best, best_time, best_transfers


"""Transfer minimization variants"""
#a
def tabu_search_transfer_basic(graph: dict[str, list[GraphEdge]], start: str, targets: list[str], start_time: int, max_iterations: int = 100) -> tuple[list[str], int, int]:
    route = [start] + targets + [start]
    s_best = route[:]
    
    tabu_list = []
    iteration = 0
    
    while iteration < max_iterations:
        neighbors = get_2opt_neighbors(route)
        best_neighbor = None
        best_neighbor_cost = (float('inf'), float('inf'))  
        best_neighbor_move = None
        
        for neighbor_route, move in neighbors:
            if move not in tabu_list:
                transfers, time_cost = calculate_route_cost_transfers(graph, neighbor_route, start_time)
                cost = (transfers, time_cost)
                if cost < best_neighbor_cost:
                    best_neighbor = neighbor_route
                    best_neighbor_cost = cost
                    best_neighbor_move = move
        
        if best_neighbor is None:
            break
        
        route = best_neighbor
        transfers, time_cost = calculate_route_cost_transfers(graph, route, start_time)
        
        best_transfers, best_time = calculate_route_cost_transfers(graph, s_best, start_time)
        if (transfers, time_cost) < (best_transfers, best_time):
            s_best = route[:]
        
        if best_neighbor_move:
            tabu_list.append(best_neighbor_move)
        
        iteration += 1
    
    best_transfers, best_time = calculate_route_cost_transfers(graph, s_best, start_time)
    return s_best, best_transfers, best_time

#b
def tabu_search_transfer_variable_t(graph: dict[str, list[GraphEdge]], start: str, targets: list[str], start_time: int, max_iterations: int = 100) -> tuple[list[str], int, int]:
    route = [start] + targets + [start]
    s_best = route[:]
    
    tabu_size = max(3, len(targets) // 2 + 1)
    tabu_list = []
    iteration = 0
    
    while iteration < max_iterations:
        neighbors = get_2opt_neighbors(route)
        best_neighbor = None
        best_neighbor_cost = (float('inf'), float('inf'))
        best_neighbor_move = None
        
        for neighbor_route, move in neighbors:
            if move not in tabu_list:
                transfers, time_cost = calculate_route_cost_transfers(graph, neighbor_route, start_time)
                cost = (transfers, time_cost)
                if cost < best_neighbor_cost:
                    best_neighbor = neighbor_route
                    best_neighbor_cost = cost
                    best_neighbor_move = move
        
        if best_neighbor is None:
            break
        
        route = best_neighbor
        transfers, time_cost = calculate_route_cost_transfers(graph, route, start_time)
        
        best_transfers, best_time = calculate_route_cost_transfers(graph, s_best, start_time)
        if (transfers, time_cost) < (best_transfers, best_time):
            s_best = route[:]
        
        if best_neighbor_move:
            tabu_list.append(best_neighbor_move)
            if len(tabu_list) > tabu_size:
                tabu_list.pop(0)
        
        iteration += 1
    
    best_transfers, best_time = calculate_route_cost_transfers(graph, s_best, start_time)
    return s_best, best_transfers, best_time

#c
def tabu_search_transfer_aspiration(graph: dict[str, list[GraphEdge]], start: str, targets: list[str], start_time: int, max_iterations: int = 100) -> tuple[list[str], int, int]:
    route = [start] + targets + [start]
    s_best = route[:]
    best_transfers, best_time = calculate_route_cost_transfers(graph, s_best, start_time)
    
    tabu_size = max(3, len(targets) // 2 + 1)
    tabu_list = []
    iteration = 0
    
    while iteration < max_iterations:
        neighbors = get_2opt_neighbors(route)
        best_neighbor = None
        best_neighbor_cost = (float('inf'), float('inf'))
        best_neighbor_move = None
        
        for neighbor_route, move in neighbors:
            transfers, time_cost = calculate_route_cost_transfers(graph, neighbor_route, start_time)
            cost = (transfers, time_cost)
            
            if move not in tabu_list or transfers < best_transfers:
                if cost < best_neighbor_cost:
                    best_neighbor = neighbor_route
                    best_neighbor_cost = cost
                    best_neighbor_move = move
        
        if best_neighbor is None:
            break
        
        route = best_neighbor
        transfers, time_cost = calculate_route_cost_transfers(graph, route, start_time)
        
        if (transfers, time_cost) < (best_transfers, best_time):
            s_best = route[:]
            best_transfers, best_time = transfers, time_cost
        
        if best_neighbor_move:
            tabu_list.append(best_neighbor_move)
            if len(tabu_list) > tabu_size:
                tabu_list.pop(0)
        
        iteration += 1
    
    best_transfers, best_time = calculate_route_cost_transfers(graph, s_best, start_time)
    return s_best, best_transfers, best_time

#d
def tabu_search_transfer_sampling(graph: dict[str, list[GraphEdge]], start: str, targets: list[str], start_time: int,max_iterations: int = 100) -> tuple[list[str], int, int]:
    
    route = [start] + targets + [start]
    s_best = route[:]
    
    tabu_size = max(3, len(targets) // 2 + 1)
    tabu_list = []
    iteration = 0
    
    max_sample_size = min(20, max(5, int((len(targets) ** 1.5) / 2)))
    
    while iteration < max_iterations:
        neighbors = get_2opt_neighbors(route, sample_size=max_sample_size)
        best_neighbor = None
        best_neighbor_cost = (float('inf'), float('inf'))
        best_neighbor_move = None
        
        for neighbor_route, move in neighbors:
            if move not in tabu_list:
                transfers, time_cost = calculate_route_cost_transfers(graph, neighbor_route, start_time)
                cost = (transfers, time_cost)
                if cost < best_neighbor_cost:
                    best_neighbor = neighbor_route
                    best_neighbor_cost = cost
                    best_neighbor_move = move
        
        if best_neighbor is None:
            break
        
        route = best_neighbor
        transfers, time_cost = calculate_route_cost_transfers(graph, route, start_time)
        
        best_transfers, best_time = calculate_route_cost_transfers(graph, s_best, start_time)
        if (transfers, time_cost) < (best_transfers, best_time):
            s_best = route[:]
        
        if best_neighbor_move:
            tabu_list.append(best_neighbor_move)
            if len(tabu_list) > tabu_size:
                tabu_list.pop(0)
        
        iteration += 1
    
    best_transfers, best_time = calculate_route_cost_transfers(graph, s_best, start_time)
    return s_best, best_transfers, best_time
