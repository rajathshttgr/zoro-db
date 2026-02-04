package core

type CollectionInfo struct {
	ID        int
	Name      string
	Dimension int
	Distance  string
	Status    string
	CreatedAt string
}

type PointRetrival struct {
	Status  string
	PointId int
	Payload map[string]any
}

type SearchPoint struct {
	PointId int
	Score   float32
	Payload map[string]any
}

type SearchPointRetrival struct {
    Points []*SearchPoint `json:"points"`
    Count  int            `json:"count"`
}

type ScrollPoint struct {
	PointId int
	Payload map[string]any
}

type ScrollPointsRetrival struct {
    Points []*ScrollPoint `json:"points"`
    Count  int            `json:"count"`
}
