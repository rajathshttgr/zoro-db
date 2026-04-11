package dto

type VectorConfig struct {
    Size        int    `json:"size" binding:"required"`
    Distance    string `json:"distance" binding:"required"`
}

type CreateCollectionRequest struct {
    Vectors  VectorConfig `json:"vectors" binding:"required"`
}

type CreateCollectionResult struct {
	Result	   bool 	`json:"result"`
	Status     string 	`json:"status"`
	Time  	   float64 	`json:"time"`
}

type DeleteCollectionResult struct {
	Result	   bool 	`json:"result"`
	Status     string 	`json:"status"`
	Time  	   float64 	`json:"time"`
}

type CollectionInfo struct {
	Name     string `json:"name"`
	Size     int    `json:"size"`
	Distance string `json:"distance"`
	Status   string `json:"status"`
}

type CollectionsResult struct {
	CollectionCount  int               `json:"collections_count"`
	Collections      []CollectionInfo  `json:"collections"`
}

type CollectionExists struct {
	Exists	   bool 	`json:"exists"`
}

type VectorConfigDetails struct{
	Size        int    `json:"size"`
    Distance    string `json:"distance"`
}

type ConfigDetails struct{
	Name  		 string  				`json:"name"`
	InternalId   string  				`json:"internal_id`
	Vectors      VectorConfigDetails	`json:"vectors""`
}

type CollectionDetails struct {
    Status         string         `json:"status"`
	PointsCount	   int 	          `json:"points_count"`
	SegmentCount   int            `json:"segments_count"`
	Config		   ConfigDetails  `json:"config"`
}
