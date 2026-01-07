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