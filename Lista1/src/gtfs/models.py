# GTFS Models

class Agency:
    def __init__(self, agency_id, agency_name, agency_url, agency_timezone, agency_phone, agency_email, agency_fare_url):
        self.agency_id = agency_id
        self.agency_name = agency_name
        self.agency_url = agency_url
        self.agency_timezone = agency_timezone
        self.agency_phone = agency_phone
        self.agency_email = agency_email
        self.agency_fare_url = agency_fare_url
        
        
class Route:
    def __init__(self, route_id, agency_id, route_short_name, route_long_name, route_type, route_color, route_text_color):
        self.route_id = route_id
        self.agency_id = agency_id
        self.route_short_name = route_short_name
        self.route_long_name = route_long_name
        self.route_type = route_type
        self.route_color = route_color
        self.route_text_color = route_text_color
        
class Stop:
    def __init__(self, stop_id, stop_code, stop_name, stop_desc,stop_lat, stop_lon, location_type, parent_station, platform_code):
        self.stop_id = stop_id
        self.stop_code = stop_code
        self.stop_name = stop_name
        self.stop_desc = stop_desc
        self.stop_lat = stop_lat
        self.stop_lon = stop_lon
        self.location_type = location_type
        self.parent_station = parent_station
        self.platform_code = platform_code
        
class Trip:
    def __init__(self, route_id, service_id, trip_id, trip_headsign, direction_id, block_id):
        self.route_id = route_id
        self.service_id = service_id
        self.trip_id = trip_id
        self.trip_headsign = trip_headsign
        self.direction_id = direction_id
        self.block_id = block_id
        
class StopTime:
    def __init__(self, trip_id, arrival_time, departure_time, stop_id, stop_sequence, stop_headsign, pickup_type, shape_dist_traveled):
        self.trip_id = trip_id
        self.arrival_time = arrival_time
        self.departure_time = departure_time
        self.stop_id = stop_id
        self.stop_sequence = stop_sequence
        self.stop_headsign = stop_headsign
        self.pickup_type = pickup_type
        self.shape_dist_traveled = shape_dist_traveled
        
class Calendar:
    def __init__(self, service_id, monday, tuesday, wednesday, thursday, friday, saturday, sunday, start_date, end_date):
        self.service_id = service_id
        self.monday = monday
        self.tuesday = tuesday
        self.wednesday = wednesday
        self.thursday = thursday
        self.friday = friday
        self.saturday = saturday
        self.sunday = sunday
        self.start_date = start_date
        self.end_date = end_date
        
class CalendarDate:
    def __init__(self, service_id, date, exception_type):
        self.service_id = service_id
        self.date = date
        self.exception_type = exception_type
        
class feed_info:
    def __init__(self, feed_publisher_name, feed_publisher_url, feed_lang, feed_start_date, feed_end_date):
        self.feed_publisher_name = feed_publisher_name
        self.feed_publisher_url = feed_publisher_url
        self.feed_lang = feed_lang
        self.feed_start_date = feed_start_date
        self.feed_end_date = feed_end_date
                      