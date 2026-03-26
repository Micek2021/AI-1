import heapq
from gtfs.graph_builder import GraphEdge
from gtfs.models import Stop

def heuristic(stop_id: str, end_stop_id: str, stops: dict[str, Stop]) -> int:
    stop = stops.get(stop_id)
    end_stop = stops.get(end_stop_id)
    
    if stop is None or end_stop is None:
        return 0
    
    lat_diff = abs(stop.stop_lat - end_stop.stop_lat)
    lon_diff = abs(stop.stop_lon - end_stop.stop_lon)
    
    distance_km = (lat_diff + lon_diff) * 111  
    estimated_time = distance_km / 80 * 60  
    
    return int(estimated_time)

def astar_time(graph: dict[str, list[GraphEdge]], start_stop_id: str, end_stop_id: str, start_time: int, stops: dict[str, Stop]) -> list[GraphEdge]:
    counter = 0
    
    queue = [(start_time + heuristic(start_stop_id, end_stop_id, stops), counter, start_time, start_stop_id, [])]
    best_time = {start_stop_id: start_time}
    while queue:
        _, _, current_time, current_stop, path = heapq.heappop(queue)
        
        if current_stop == end_stop_id:
            return path
        
        if current_time > best_time.get(current_stop, float('inf')):
            continue
        
        for edge in graph.get(current_stop, []):
            if edge.departure_time < current_time:
                continue  
            
            new_time = edge.arrival_time
            
            if new_time < best_time.get(edge.end_stop_id, float('inf')):
                best_time[edge.end_stop_id] = new_time
                counter += 1
                heapq.heappush(queue, (new_time + heuristic(edge.end_stop_id, end_stop_id, stops), counter, new_time, edge.end_stop_id, path + [edge]))
    
    return []             

def build_trips_arriving(graph: dict[str, list[GraphEdge]]) -> dict[str, set[str]]:
    trips_arriving = {}
    for edges in graph.values():
        for edge in edges:
            trips_arriving.setdefault(edge.end_stop_id, set()).add(edge.trip_id)
    return trips_arriving

def build_trips_departing(graph: dict[str, list[GraphEdge]]) -> dict[str, set[str]]:
    return {stop_id: {edge.trip_id for edge in edges} for stop_id, edges in graph.items()}

def heuristic_transfer(stop_id: str, end_stop_id: str, trips_departing: dict[str, set[str]], trips_arriving: dict[str, set[str]]) -> int:
    if stop_id == end_stop_id:
        return 0
    trips_at_current = trips_departing.get(stop_id, set())
    trips_at_end = trips_arriving.get(end_stop_id, set())
    return 0 if trips_at_current & trips_at_end else 1

def astar_transfer(graph: dict[str, list[GraphEdge]], start_stop_id: str, end_stop_id: str, start_time: int) -> list[GraphEdge]:
    counter = 0
    trips_arriving = build_trips_arriving(graph)
    trips_departing = build_trips_departing(graph)
    h0 = heuristic_transfer(start_stop_id, end_stop_id, trips_departing, trips_arriving)
    queue = [(h0, 0, start_time, counter, start_stop_id, '', [])]
    best = {(start_stop_id, ''): (0, start_time)}
    
    while queue:
        _, current_transfers, current_time, __, current_stop, current_trip, path = heapq.heappop(queue)
        
        if current_stop == end_stop_id:
            return path
        
        key = (current_stop, current_trip)
        if (current_transfers, current_time) > best.get(key, (float('inf'), float('inf'))):
            continue
        
        for edge in graph.get(current_stop, []):
            if edge.departure_time < current_time:
                continue
            
            new_transfers = current_transfers + (1 if current_trip and current_trip != edge.trip_id else 0)
            new_time = edge.arrival_time
            
            new_key = (edge.end_stop_id, edge.trip_id)
            new_best = (new_transfers, new_time)
            
            if new_best < best.get(new_key, (float('inf'), float('inf'))):
                best[new_key] = new_best
                h = heuristic_transfer(edge.end_stop_id, end_stop_id, trips_departing, trips_arriving)
                counter += 1
                heapq.heappush(queue, (new_transfers + h, new_transfers, new_time, counter, edge.end_stop_id, edge.trip_id, path + [edge]))
                
    return []