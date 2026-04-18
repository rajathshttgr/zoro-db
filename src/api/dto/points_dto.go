package dto

type ID int
// TODO: Support unsigned int and uuid as ID types

type PointData struct {
	Id      ID            `json:"id" binding:"required,gte=0`
	Vector  []float32       `json:"vector" binding:"required,min=1"`
	Payload map[string]any  `json:"payload,omitempty"`
}

type UpsertPointsRequest struct {
	Points []PointData `json:"points" binding:"required,min=1,dive"`
}

type UpsertPointsResult struct {
	Status         string `json:"status"`
	Operation_Id   int    `json:"operation_id"`
}