import heapq
from gtfs.graph_builder import GraphEdge

def dijkstra(graph: dict[str, list[GraphEdge]], start_stop_id: str, end_stop_id: str, start_time: int) -> list[GraphEdge]:
    counter = 0
    queue = [(start_time, counter, start_stop_id, '', [])]
    best_time = {start_stop_id: start_time}
    
    while queue:
        current_time, _, current_stop, current_trip, path = heapq.heappop(queue)
        
        if current_stop == end_stop_id:
            num_transfers = sum(1 for i in range(1, len(path)) if path[i].trip_id != path[i-1].trip_id)
            return path, current_time, num_transfers
        
        if current_time > best_time.get(current_stop, float('inf')):
            continue
        
        for edge in graph.get(current_stop, []):
            if edge.departure_time < current_time:
                continue  
            
            new_time = edge.arrival_time
            
            if new_time < best_time.get(edge.end_stop_id, float('inf')):
                best_time[edge.end_stop_id] = new_time
                counter += 1
                heapq.heappush(queue, (new_time, counter, edge.end_stop_id, edge.trip_id, path + [edge]))
    
    return [], float('inf'), float('inf')