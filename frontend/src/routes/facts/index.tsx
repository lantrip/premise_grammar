import { $api } from "@/lib/api/client";
import {
  Table,
  TableBody,
  TableCell,
  TableHead,
  TableHeader,
  TableRow,
} from "@/components/ui/table";
import { Badge } from "@/components/ui/badge";

export default function FactsPage() {
  const { data, isLoading, error } = $api.useQuery("get", "/api/facts");
  if (isLoading) return <div>Loading…</div>;
  if (error) return <div>Error loading facts</div>;
  const facts = data ?? [];
  return (
    <div className="space-y-4">
      <h2 className="text-xl font-semibold">Facts ({facts.length})</h2>
      <Table>
        <TableHeader>
          <TableRow>
            <TableHead>Type</TableHead>
            <TableHead>Fact</TableHead>
            <TableHead>Entities</TableHead>
            <TableHead>Confidence</TableHead>
            <TableHead>Importance</TableHead>
          </TableRow>
        </TableHeader>
        <TableBody>
          {facts.map((f) => (
            <TableRow key={f.id}>
              <TableCell>
                <Badge variant="outline">{f.type}</Badge>
              </TableCell>
              <TableCell className="max-w-[480px] whitespace-pre-wrap">
                {f.fact}
              </TableCell>
              <TableCell>
                <div className="flex flex-wrap gap-1">
                  {f.entities?.map((e) => (
                    <Badge key={e} variant="secondary">
                      {e}
                    </Badge>
                  )) ??
                    (f.entity ? (
                      <Badge variant="secondary">{f.entity}</Badge>
                    ) : null)}
                </div>
              </TableCell>
              <TableCell>{f.confidence?.toFixed?.(2) ?? "—"}</TableCell>
              <TableCell>{f.importance?.score?.toFixed?.(2) ?? "—"}</TableCell>
            </TableRow>
          ))}
        </TableBody>
      </Table>
    </div>
  );
}



