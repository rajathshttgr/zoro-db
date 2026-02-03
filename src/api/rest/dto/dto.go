package dto


type ErrorResponse struct {
    Error string `json:"error"`
}

type CreateCollectionRequest struct {
    CollectionName  string `json:"collection_name" binding:"required"`
    Dimension       int    `json:"dimension" binding:"required"`
    Distance        string `json:"distance" binding:"required"`
}

type CollectionResponseLayout struct {
	Result any     `json:"result"`
	Time   float64 `json:"time"`
}

type CreateCollectionResult struct {
	Status         string `json:"status"`
	CollectionName string `json:"collection_name"`
	Dimension      int    `json:"dimension"`
	Distance       string `json:"distance"`
	Sharding       int    `json:"sharding"`
}

type DeleteCollectionResult struct {
	Status         string `json:"status"`
	CollectionName string `json:"collection_name"`
}

type CollectionInfoResult struct {
    CollectionName string `json:"collection_name"`
    Dimension      string `json:"dimension"`
    Distance       string `json:"distance"`
    Status         string `json:"status"`
}


type UpsertPointsRequest struct {
	Vectors [][]float32       `json:"vectors" binding:"required"`
	Ids     []int          `json:"ids" binding:"required"`
	Payload []map[string]any  `json:"payload"`
}

type DeletePointsRequest struct {
	Ids []int `json:"ids" binding:"required"`
}

type UpsertPointsResult struct {
	Status         string `json:"status"`
	CollectionName string `json:"collection_name"`
	Upserted       int    `json:"upserted"`
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