package dto


type ErrorResponse struct {
    Error string `json:"error"`
}

type ResponseLayout struct {
	Result     any      `json:"result"`
	Status     string 	`json:"status"`
	Time  	   float64 	`json:"time"`
}


type CollectionResponseLayout struct {
	Result any     `json:"result"`
	Time   float64 `json:"time"`
}

type DeletePointsRequest struct {
	Ids []int `json:"ids" binding:"required"`
}

type DeletePointsResult struct {
	Status         string `json:"status"`
	CollectionName string `json:"collection_name"`
	Deleted        int    `json:"deleted"`
}


type CollectionPointsInfoResult struct {
	CollectionName string `json:"collection_name"`
	PointsCount    int    `json:"points_count"`
	Status         string `json:"status"`
}


type PointRetriveResult struct{
	Status		string			`json:"status"`
	PointId		int				`json:"point_id"`
	Payload 	map[string]any	`json:"payload"`
}

type SearchPointsRequest struct{
	Vectors []float32 `json:"vectors" binding:"required"`
	Limit 	int 		`json:"limit" binding:"required"`		
}

type PointSearchResult struct{
	PointId		int				`json:"point_id"`
	Score		float32			`json:"score"`
	Payload 	map[string]any	`json:"payload"`
}

type ScrollPointsRequest struct{
	Limit 	int 		`json:"limit" binding:"required"`		
}

type PointsScrollResult struct{
	PointId		int				`json:"point_id"`
	Payload 	map[string]any	`json:"payload"`
}