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

export default function TimelinePage() {
  const { data, isLoading, error } = $api.useQuery("get", "/api/timeline");
  if (isLoading) return <div>Loading…</div>;
  if (error) return <div>Error loading timeline</div>;
  const items = data ?? [];
  return (
    <div className="space-y-4">
      <h2 className="text-xl font-semibold">Timeline ({items.length})</h2>
      <Table>
        <TableHeader>
          <TableRow>
            <TableHead>Order</TableHead>
            <TableHead>Event</TableHead>
            <TableHead>Entities</TableHead>
            <TableHead>Sources</TableHead>
          </TableRow>
        </TableHeader>
        <TableBody>
          {items.map((t) => (
            <TableRow key={t.id}>
              <TableCell className="text-xs text-muted-foreground">
                {formatOrder(t.order)}
              </TableCell>
              <TableCell className="max-w-[560px] whitespace-pre-wrap">
                {t.event}
              </TableCell>
              <TableCell>
                <div className="flex flex-wrap gap-1">
                  {t.entities.map((e) => (
                    <Badge key={e} variant="secondary">
                      {e}
                    </Badge>
                  ))}
                </div>
              </TableCell>
              <TableCell className="text-xs text-muted-foreground">
                {t.source.join(", ")}
              </TableCell>
            </TableRow>
          ))}
        </TableBody>
      </Table>
    </div>
  );
}

function formatOrder(order: any): string {
  if (typeof order === "number") return order.toString();
  if (typeof order === "string") return order;
  if (order && typeof order === "object") {
    if ("Numeric" in order) return String((order as any).Numeric);
    if ("Named" in order) return String((order as any).Named);
  }
  return "";
}



