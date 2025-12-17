package dto


type ErrorResponse struct {
    Error string `json:"error"`
}

type CreateCollectionRequest struct {
    CollectionName  string `json:"collection_name" binding:"required"`
    Dimension       int    `json:"dimension" binding:"required"`
    Distance        string `json:"distance" binding:"required"`
}

type CreateCollectionResponse struct {
	CollectionName string `json:"collection_name"`
	Dimension      int    `json:"dimension"`
	Distance       string `json:"distance"`
	Status         string `json:"status"`
}

